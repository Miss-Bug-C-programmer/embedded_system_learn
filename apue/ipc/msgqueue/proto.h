#ifndef __PROTO_H
#define __PROTO_H

#define PATHNAME	"/etc/passwd"
#define PROJ_ID		'A'

#define MSGSIZE		1024

// 数据类型
typedef struct {
	long mtype;
	char mtext[1];
}data_t;

#endif

