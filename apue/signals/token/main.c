#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "token.h"

#define BUFSIZE	10

#define CPS		10
#define BURST	10*(CPS)


int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	int fd;
	int cnt;
	char buf[BUFSIZE] = {};
	int tbfId;

	tbfId = tbfInit(CPS, BURST);
	if (-1 == tbfId) {
		fprintf(stderr, "tbfInit() failed\n");
		exit(1);
	}

	// fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	fd = open(argv[1], O_RDONLY);
	if (-1 == fd) {
		perror("open()");
		printf("open():%s\n", strerror(errno));
		return 1;
	}

	while (1) {
		// 取令牌
		tbfFetchToken(tbfId, CPS);

		cnt = read(fd, buf, CPS);	
		if (cnt == 0)
			break;
		else if (cnt == -1) {
			perror("read()");
			goto ERROR;
		}
		write(1, buf, cnt);
	}

	tbfDestroy(tbfId);
	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}

