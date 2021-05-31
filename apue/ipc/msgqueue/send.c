#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	key_t key;
	int msgid;
	data_t *d;
	int len;

	if (argc < 3)
		exit(1);

	key = ftok(PATHNAME, PROJ_ID);
	if (-1 == key) {
		perror("ftok()");
		exit(1);
	}
	// 创建/获取消息队列实例
	msgid = msgget(key, 0);
	if (-1 == msgid) {
		perror("msgget()");
		exit(1);
	}

	len = strlen(argv[2]); 
	d = malloc(sizeof(data_t) + len);
	// if error
	memset(d, '\0', sizeof(data_t)+len);
	d->mtype = atoi(argv[1]);
	strncpy(d->mtext, argv[2], MSGSIZE);

	msgsnd(msgid, d, len, 0);

	return 0;
}

