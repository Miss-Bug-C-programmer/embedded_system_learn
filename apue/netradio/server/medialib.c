#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#include "medialib.h"

#define BUFSIZE	128

struct context_st {
	int8_t chnid;
	char *descr;
	glob_t dataFilePaths;
	int musicIndex; // dataFGilePaths.gl_pathv-->index 
	int pos;
	int fd;
};

static struct context_st *mlibContext = NULL;	
static int chnnr;

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
	
	// 打开该频道的第一个音乐文件
	context->fd = open((context->dataFilePaths.gl_pathv)[0], \
			O_RDONLY);
	// if error

	return 0;
}

// 解析媒体库目录
static int parseChnDir()
{
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
	mlibContext	= calloc(res.gl_pathc, sizeof(struct context_st));

	int validChnIndex = 0;
	for (i = 0; i < res.gl_pathc; i++) {
		if (parseChnEntry((res.gl_pathv)[i], mlibContext+validChnIndex) == -1) {
			// 该频道无效
			continue;
		}
		validChnIndex++;
	}

	if (validChnIndex != res.gl_pathc)
		mlibContext = realloc(mlibContext, validChnIndex * sizeof(struct context_st));

	chnnr = validChnIndex;
}

int mlibGetChnList(mlibChnList_t **mlibArr, int *chnCnt)
{
	int i;

	parseChnDir();
	*mlibArr = calloc(chnnr, sizeof(mlibChnList_t)); 

	for (i = 0; i < chnnr; i++) {
		(*mlibArr)[i].chnid = mlibContext[i].chnid;
		(*mlibArr)[i].descr = strdup(mlibContext[i].descr);
	}

	*chnCnt = chnnr;

	return 0;
}

static int openNext(int8_t chnid)
{
	struct context_st *p = mlibContext+chnid-1; 

	p->musicIndex = (p->musicIndex+1) % (p->dataFilePaths).gl_pathc;
	p->fd = open((p->dataFilePaths.gl_pathv)[p->musicIndex], O_RDONLY);
	// if error;
	p->pos = 0;

	return 0;
}

// 数据
int mlibReadChnData(int8_t chnid, void *buf, size_t size)
{
	while (1) {
		int cnt = pread(mlibContext[chnid-1].fd, buf, size, \
				mlibContext[chnid-1].pos);	
		if (cnt == -1) {
			perror("pread()");
			return -1;
		}
		if (cnt == 0) {
			// 打开下一个音乐文件
			openNext(chnid);
			continue;
		}
		mlibContext[chnid-1].pos += cnt;
		break;
	}

	return 0;
}

