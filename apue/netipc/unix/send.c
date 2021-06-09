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
	struct sockaddr_un raddr;

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	raddr.sun_family = AF_UNIX;
	strcpy(raddr.sun_path, PATHNAME);
	sendto(sd, "hello", 5, 0, (void *)&raddr, \
			offsetof(struct sockaddr_un, sun_path)+\
			strlen(raddr.sun_path)+1);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

