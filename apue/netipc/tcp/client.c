#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in raddr;

	sd = socket(AF_INET, SOCK_STREAM, 0);	
	// if error;

//	bind();	

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(SERVERPORT);
	inet_aton(SERVERIP, &raddr.sin_addr);
	if (connect(sd, (void *)&raddr, sizeof(raddr)) == -1) {
		perror("connect()");
		goto ERROR;
	}

	write(sd, "abcdefg", 7);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

