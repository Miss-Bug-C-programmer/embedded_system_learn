#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>
#include <mainproto.h>
#include <stdlib.h>

#include "thrChnData.h"
#include "medialib.h"

extern int serverSd;

static void *thrData(void *arg)
{
	int8_t id = (int8_t)arg;
	struct listData_st *d;
	struct sockaddr_in groupAddr;
	int msglen;
	int readCnt;

	// 总大小
	d = malloc(MSGSIZE);
	// if error;
	// 音乐数据大小
	msglen = MSGSIZE - sizeof(int8_t);
	
	groupAddr.sin_family = AF_INET;
	inet_aton(MULTICASTIP, &groupAddr.sin_addr);
	groupAddr.sin_port = htons(RCVPORT);

	d->chnId = id;
	while (1) {
		memset(d->chnmsg, '\0', msglen);
		readCnt = mlibReadChnData(id, d->chnmsg, msglen);		
		sendto(serverSd, d, readCnt+sizeof(int8_t), 0, \
				(void *)&groupAddr, sizeof(groupAddr));
		sleep(1);
	}
}

int createThrChnData(int8_t chnid)
{
	pthread_t tid;

	pthread_create(&tid, NULL, thrData, (void *)chnid);	
	// if error;
}

