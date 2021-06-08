#include <stdio.h>
#include <stdlib.h>
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
	struct sockaddr_in laddr;
	struct ip_mreqn imq;
	char buf[MSGSIZE] = {};

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	inet_aton("0.0.0.0", &laddr.sin_addr);
	laddr.sin_port = htons(RCVPORT);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	// 加入多播组
	inet_aton(MULTIIP, &imq.imr_multiaddr);
	inet_aton("0.0.0.0", &imq.imr_address);
	imq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imq, sizeof(imq)) == -1) {
		perror("setsockopt()");
		exit(1);
	}

	if (recvfrom(sd, buf, MSGSIZE, 0, NULL, NULL) == -1) {
		perror("recvfrom()");
		exit(1);
	}
	puts(buf);

	close(sd);

	exit(0);
}

