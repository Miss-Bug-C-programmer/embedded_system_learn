#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#include "medialib.h"

#define BUFSIZE	128

struct context_st {
	int8_t chnid;
	char *descr;
	glob_t dataFilePaths;
	int musicIndex; // dataFilePaths.gl_pathv-->index 
	int pos;
};

static int parseChnEntry(const char *chnPath, struct context_st *context)
{
	char buf[BUFSIZE] = {};
	FILE *fp;
	char *ptr = NULL;
	size_t n = 0;
	static int id = 1;

	strcpy(buf, chnPath);
	strcat(buf, "/descr.txt");
	fp = fopen(buf, "r");
	if (NULL == fp) {
		perror("fopen()");
		return -1;
	}
	getline(&ptr, &n, fp);
	context->descr = ptr;

	// 读音乐
	memset(buf, '\0', BUFSIZE);
	strcpy(buf, chnPath);
	strcat(buf, "/*.mp3");
	glob(buf, GLOB_NOSORT, NULL, &context->dataFilePaths);
	if ((context->dataFilePaths).gl_pathc == 0) {
		// 没有音乐
		free(ptr);
		return -1;
	}

	context->chnid = id++;
	context->pos = 0;
	context->musicIndex = 0;

	return 0;
}

// 解析媒体库目录
static int parseChnDir(struct context_st **mlibContext, int *chnnr)
{
	struct context_st *p = NULL;
	char buf[BUFSIZE] = {};
	glob_t res;
	int i;
	FILE *fp;

	// MEDIALIBPATH/*
	strcpy(buf, MEDIALIBPATH);
	strcat(buf, "/*");
	puts(buf);
	if (glob(buf, GLOB_NOSORT, NULL, &res) != 0) {
		fprintf(stderr, "[%d][%s]glob() failed\n", __LINE__, __FUNCTION__);
		return -1;
	}
	p = calloc(res.gl_pathc, sizeof(struct context_st));

	int validChnIndex = 0;
	for (i = 0; i < res.gl_pathc; i++) {
		if (parseChnEntry((res.gl_pathv)[i], p+validChnIndex) == -1) {
			// 该频道无效
			continue;
		}
		validChnIndex++;
	}

	if (validChnIndex != res.gl_pathc)
		p = realloc(p, validChnIndex * sizeof(struct context_st));

	*mlibContext = p;
	*chnnr = validChnIndex;
}

int mlibGetChnList(mlibChnList_t **mlibArr, int *chnCnt)
{
	struct context_st *p = NULL;	
	int chnnr;
	int i;

	parseChnDir(&p, &chnnr);
	*mlibArr = calloc(chnnr, sizeof(mlibChnList_t)); 

	for (i = 0; i < chnnr; i++) {
		(*mlibArr)[i].chnid = p[i].chnid;
		(*mlibArr)[i].descr = strdup(p[i].descr);
	}

	*chnCnt = chnnr;

	return 0;
}

// 数据
int mlibReadChnData(int8_t chnid, void *buf, size_t size)
{

}

