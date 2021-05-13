#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	int fd;
	int cnt;
	char buf[BUFSIZE] = {};

	// fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd) {
		perror("open()");
		printf("open():%s\n", strerror(errno));
		return 1;
	}

	while (1) {
		cnt = read(fd, buf, BUFSIZE);	
		if (cnt == 0)
			break;
		else if (cnt == -1) {
			perror("read()");
			goto ERROR;
		}
		write(1, buf, cnt);
	}

	printf("fd:%d\n", fd);

	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}

