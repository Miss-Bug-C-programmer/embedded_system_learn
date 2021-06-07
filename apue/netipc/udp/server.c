#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "proto.h"

static char *names[] = {"凯歌", "泽天", "大光", "大个", "雪瑶",\
"孙哲", "文阔", "程超", "晓周", "晋夫", "文明", NULL};

int main(void)
{
	int serverSd;
	struct sockaddr_in localAddr, remoteAddr;
	socklen_t remoteAddrLen;
	struct clientData_st rcvData;
	struct sigaction act;
	pid_t pid;
	struct serverData_st sendData;

	// 子进程不变成僵尸进程
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	serverSd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == serverSd) {
		perror("socket()");
		exit(1);
	}

	// 绑定本地地址
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(SERVERPORT);
	inet_aton(SERVERIP, &localAddr.sin_addr);
	if (bind(serverSd, (struct sockaddr *)&localAddr, sizeof(localAddr)) == -1 ) {
		perror("bind()");
		goto ERROR;
	}

	remoteAddrLen = sizeof(remoteAddr); //!!!!
	while (1) {
		if (recvfrom(serverSd, &rcvData, sizeof(rcvData), 0, \
				(void *)&remoteAddr, &remoteAddrLen) == -1) {
			perror("recvfrom()");
			goto ERROR;
		}
		printf("[rcv from]ip:%s, port:%d\n", \
				inet_ntoa(remoteAddr.sin_addr), ntohs(remoteAddr.sin_port));


		pid = fork();
		if (-1 == pid) {
			perror("fork()");		
			goto ERROR;
		}
		if (pid == 0) {
			int i;
			for (i = 0; names[i]; i++) {
				if (strcmp(names[i], rcvData.name) == 0) {
					// 存在此学生		
					strcpy(sendData.msg, "SUCCESSFULLY");
					break;
				}
			}
			if (names[i] == NULL) {
			// 没有该学生
				strcpy(sendData.msg, "NOT EXISTS");
			}
			sendto(serverSd,  &sendData, 12, 0, \
					(void *)&remoteAddr, remoteAddrLen);
			exit(0);
		}
	}

	close(serverSd);

	exit(0);
ERROR:
	close(serverSd);
	exit(1);
}

