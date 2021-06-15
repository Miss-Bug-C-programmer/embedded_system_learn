#ifndef __MEDIALIB_H
#define __MEDIALIB_H

// 提供获取频道列表和频道数据两个接口

#define MEDIALIBPATH	"/home/emb0105/medialib"

#include <stdint.h>

typedef struct {
	int8_t chnid;
	char *descr;
}mlibChnList_t;

int mlibGetChnList(mlibChnList_t **mlibArr, int *chnCnt);

// 数据
int mlibReadChnData(int8_t chnid, void *buf, size_t size);

#endif

