#ifndef __PROTO_H
#define __PROTO_H

#define SERVERIP	"10.10.1.237"
#define SERVERPORT	1111

#define NAMESIZE	32
#define MSGSIZE		128

struct clientData_st{
	uint8_t id;
	char name[NAMESIZE];
}__attribute__((packed)); 

struct serverData_st {
	char msg[MSGSIZE];
};

#endif

