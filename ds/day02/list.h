#ifndef __LIST_H
#define __LIST_H

struct node_st {
	void *data;
	struct node_st *next;
};

typedef struct {
	struct node_st node;
	int size;
}listhead_t;

enum {HEADINSERT, TAILINSERT};
typedef void (*pri_t)(const void *);
typedef int (*cmp_t)(const void *data, const void *key);

int listheadInit(int size, listhead_t **l);

int listInsert(listhead_t *h, const void *data, int way);

void listTraval(const listhead_t *h, pri_t p);

// 查找
void *listSearch(const listhead_t *h, const void *key, cmp_t cmp);

// 删除
int listDelete(listhead_t *h, const void *key, cmp_t cmp);

// 摘除 == 删除结点前copy数据
int listFetch(listhead_t *h, const void *key, cmp_t cmp, void *data);

void listDestroy(listhead_t *h);

#endif

