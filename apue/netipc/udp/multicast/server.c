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
	struct ip_mreqn imq;
	struct sockaddr_in raddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	inet_aton(MULTIIP, &imq.imr_multiaddr);
	inet_aton("0.0.0.0", &imq.imr_address);
	imq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &imq, sizeof(imq)) == -1) {
		perror("setsockopt()");
		close(sd);
		exit(1);
	}

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton(MULTIIP, &raddr.sin_addr);
	while (1) {
		sendto(sd, "good morning", 12, 0, (void *)&raddr, sizeof(raddr));
		sleep(1);
	}

	close(sd);

	exit(0);
}

