#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	int sd, newsd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	pid_t pid;

	sd = socket(AF_INET, SOCK_STREAM, 0);	
	// if error

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(SERVERPORT);
	inet_aton(SERVERIP, &laddr.sin_addr);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	if (listen(sd, 20) == -1) {
		perror("listen()");
		goto ERROR;
	}

	raddrlen = sizeof(raddr);
	while (1) {
		newsd = accept(sd, (void *)&raddr, &raddrlen);
		if (-1 == newsd) {
			perror("accept()");
			goto ERROR;
		}
		printf("connect client ip:%s, port:%d\n", \
				inet_ntoa(raddr.sin_addr), ntohs(raddr.sin_port));

		// newsd 已经创建连接的套接字
		pid = fork();
		// if error;
		if (0 == pid) {
			// 数据交换
			char buf[MSGSIZE] = {};
			read(newsd, buf, MSGSIZE);
			puts(buf);
			close(newsd);
			exit(0);
		}
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

