#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <sys/types.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in raddr;
	int val;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 使能广播选项
	val = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) == -1) {
		perror("setsockopt()");
		close(sd);
		exit(1);
	}

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton("255.255.255.255", &raddr.sin_addr);
	while (1) {
		sendto(sd, "good afternoon", 14, 0, (void *)&raddr, sizeof(raddr));
		sleep(1);
	}

	close(sd);

	exit(0);
}

