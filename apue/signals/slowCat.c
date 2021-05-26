#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define BUFSIZE	10

/*
 令牌桶三要素:
 	速率
	令牌
	上限
 */
#define CPS		10
#define BURST	10*(CPS)

static int token; // 令牌

static void alrmHandler(int s)
{
	alarm(1);
	token += CPS;
	if (token >= BURST)
		token = BURST;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	int fd;
	int cnt;
	char buf[BUFSIZE] = {};

	signal(SIGALRM, alrmHandler);
	alarm(1);

	// fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd) {
		perror("open()");
		printf("open():%s\n", strerror(errno));
		return 1;
	}

	while (1) {
		// 取令牌
		while (token <= 0)
			pause(); // 通知法
		token -= CPS;
		cnt = read(fd, buf, CPS);	
		if (cnt == 0)
			break;
		else if (cnt == -1) {
			perror("read()");
			goto ERROR;
		}
		write(1, buf, cnt);
	}

	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}

