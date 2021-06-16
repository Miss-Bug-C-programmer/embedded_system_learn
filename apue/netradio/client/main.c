#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <mainproto.h>

static int socketInit(int *sd)
{
	struct sockaddr_in laddr;
	struct ip_mreqn imr;

	*sd = socket(AF_INET, SOCK_DGRAM, 0);
	// if error
	laddr.sin_family = AF_INET;
	inet_aton("0.0.0.0", &laddr.sin_addr);
	laddr.sin_port = htons(RCVPORT);
	if (bind(*sd, (void *)&laddr, sizeof(laddr)) != 0) {
		perror("bind()");
		return -1;
	}

	inet_aton(MULTICASTIP, &imr.imr_multiaddr);
	inet_aton("0.0.0.0", &imr.imr_address);
	imr.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(*sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(imr)) != 0) {
		perror("setsockopt()");
		close(*sd);
		return -1;
	}

	return 0;
}

int main(void)
{
	int sd;
	struct list_st *list;
	int len;
	struct listEntry_st *listEntry;

	// 初始化套接字
	socketInit(&sd);

	// 收包---》是否是频道列表
	list = malloc(MSGSIZE);
	while (1) {
		len = recvfrom(sd, list, MSGSIZE, 0, NULL, NULL);	
		if (len < 0) {
			perror("recvfrom()");
			goto ERROR;
		}
		if (list->chnId != 0)
			continue;
		break;
	}

	// 接收到频道列表
	for (listEntry = (char *)list+sizeof(int8_t); \
			listEntry < (char *)list+len; \
			listEntry = (char *)listEntry+listEntry->len) {
		printf("listEntry:%p\n", listEntry);
		printf("list:%p\n", list);
		printf("len:%d\n", listEntry->len);
		printf("%d %s\n", listEntry->chnId, listEntry->dscr);
		sleep(1);
	}


	exit(0);
ERROR:
	close(sd);
	exit(1);
}
