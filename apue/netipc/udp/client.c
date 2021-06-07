#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int clientSd;
	struct clientData_st sndData;
	struct sockaddr_in serverAddr;
	struct serverData_st rcvData;

	if (argc < 3)
		exit(1);

	clientSd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == clientSd) {
		perror("socket()");
		exit(1);
	}

	// bind()
	sndData.id = atoi(argv[1]);
	strncpy(sndData.name, argv[2], NAMESIZE);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVERPORT);
	inet_aton(SERVERIP, &serverAddr.sin_addr);
	sendto(clientSd, &sndData, sizeof(int8_t)+strlen(argv[2]), 0, \
				(void *)&serverAddr, sizeof(serverAddr));

	recvfrom(clientSd, &rcvData, MSGSIZE, 0, NULL, NULL);
	puts(rcvData.msg);

	close(clientSd);

	exit(0);
}

