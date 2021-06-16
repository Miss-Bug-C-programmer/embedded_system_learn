#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <mainproto.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "thrChnList.h"

static const mlibChnList_t *mlib;
static int chnCnt;
extern int serverSd;

static void *thrList(void *s)
{
	struct list_st *list;	
	struct listEntry_st *entry;
	int size = 0;
	int sum = 0;
	struct sockaddr_in groupAddr;
	int i;

	list = malloc(MSGSIZE);

	list->chnId = 0;
	sum = sizeof(list->chnId);
	for (i = 0; i < chnCnt; i++) {
		size = sizeof(struct listEntry_st) + strlen(mlib[i].descr);
		printf("size:%d\n", size);
		entry = malloc(size);
		entry->chnId = mlib[i].chnid;
		strcpy(entry->dscr, mlib[i].descr);
		entry->len = size;
		memcpy((char *)list+sum, entry, size);	
		sum += size;
		free(entry);
	}
	list = realloc(list, sum);

	groupAddr.sin_family = AF_INET;
	inet_aton(MULTICASTIP, &groupAddr.sin_addr);
	groupAddr.sin_port = htons(RCVPORT);
	while (1) {
		sendto(serverSd, list, sum, 0, (void *)&groupAddr, sizeof(groupAddr));
		sleep(1);
	}
}

int thrChnListStart(const mlibChnList_t *ml, int cnt)
{
	mlib = ml;	
	chnCnt = cnt;
	pthread_t tid;
	int err;

	if ((err = pthread_create(&tid, NULL, thrList, NULL)) != 0) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		return -1;
	}
	pthread_detach(tid);
}


