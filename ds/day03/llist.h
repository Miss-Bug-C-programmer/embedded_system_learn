#ifndef __LLIST_H
#define __LLIST_H

struct node_st {
	void *data;
	struct node_st *prev;
	struct node_st *next;
};

typedef struct {
	struct node_st head;
	int size;
}llisthead_t;

typedef void (*pri_t)(const void *data);
typedef int (*cmp_t)(const void *data, const void *key);

enum {LLISTINSERTHEAD, LLISTINSERTTAIL};

// 接口定义
int llistheadInit(int size, llisthead_t **l);

int llistInsert(llisthead_t *h, const void *data, int way);

void llistTraval(const llisthead_t *h, pri_t p);

// 查找
void *llistSearch(const llisthead_t *h, const void *key, cmp_t cmp);

// 删除
int llistDelete(llisthead_t *h, const void *key, cmp_t cmp);

// 摘除 == 删除结点前copy数据
int llistFetch(llisthead_t *h, const void *key, cmp_t cmp, void *data);

void llistDestroy(llisthead_t *h);

#endif

