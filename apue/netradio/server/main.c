#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <mainproto.h>

#include "medialib.h"
#include "thrChnList.h"
#include "thrChnData.h"

int serverSd;

int socketInit()
{
	struct ip_mreqn imr;

	serverSd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == serverSd) {
		perror("socket()");
		return -1;
	}
	
	inet_aton(MULTICASTIP, &imr.imr_multiaddr);
	inet_aton("0.0.0.0", &imr.imr_address);
	imr.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(serverSd, IPPROTO_IP, IP_MULTICAST_IF, &imr, sizeof(imr)) == -1) {
		perror("setsockopt()");
		close(serverSd);
		return -1;
	}

	return 0;
}

int main(void)
{
	mlibChnList_t *mlib;
	int chnnr;

	// 初始化套接字
	socketInit();

	mlibGetChnList(&mlib, &chnnr);

	// 启动发送频道列表线程
	thrChnListStart(mlib, chnnr);

	for (int i = 0; i < chnnr; i++) {
		createThrChnData(mlib[i].chnid);		
	}

	while (1)
		pause();

	// exit(0);
	pthread_exit(NULL);
}
