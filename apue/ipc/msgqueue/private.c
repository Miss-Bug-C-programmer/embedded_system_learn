#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSGSIZE	100

typedef struct {
	long mtype;
	char msg[MSGSIZE];
}data_t;

int main(void)
{
	int msgid;
	pid_t pid;
	data_t d;

	msgid = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0600);
	if (msgid == -1) {
		perror("msgget()");
		exit(1);
	}
	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}
	if (pid == 0) {
		d.mtype = 1;
		strcpy(d.msg, "good morning");
		msgsnd(msgid, &d, 12, 0);
		exit(0);
	}

	msgrcv(msgid, &d, MSGSIZE, 0, 0);
	printf("get data type:%ld, msg:%s\n", d.mtype, d.msg);
	msgctl(msgid, IPC_RMID, NULL);

	wait(NULL);

	exit(0);
ERROR:
	msgctl(msgid, IPC_RMID, NULL);
	exit(1);
}

