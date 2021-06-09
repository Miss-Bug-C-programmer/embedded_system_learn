#include <stdio.h>
#include <stddef.h> // offsetof
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

#include "unixproto.h"

int main(void)
{
	int sd;
	struct sockaddr_un laddr;
	char buf[MSGSIZE] = {};

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sun_family = AF_UNIX;
	strcpy(laddr.sun_path, PATHNAME);
	if (bind(sd, (void *)&laddr, \
			offsetof(struct sockaddr_un, sun_path)+strlen(laddr.sun_path)+1) == -1) {
		perror("offsetof()");
		goto ERROR;
	}

	recvfrom(sd, buf, MSGSIZE, 0, NULL, NULL);	
	puts(buf);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

