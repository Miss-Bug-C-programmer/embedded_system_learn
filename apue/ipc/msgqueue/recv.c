#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "proto.h"

int main(void)
{
	key_t key;
	int msgid;
	data_t *d;

	key = ftok(PATHNAME, PROJ_ID);
	if (-1 == key) {
		perror("ftok()");
		exit(1);
	}
	// 创建/获取消息队列实例
	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == msgid) {
		perror("msgget()");
		exit(1);
	}

	d = malloc(sizeof(data_t) + MSGSIZE);
	// if error
	while (1) {
		memset(d, '\0', sizeof(data_t)+MSGSIZE);
		msgrcv(msgid, d, MSGSIZE, -3, 0);	
		if (!strcmp(d->mtext, "exit"))
			break;
		printf("recv string:%s\n", d->mtext);
	}

	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}

