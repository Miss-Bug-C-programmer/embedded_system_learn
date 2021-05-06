#include <stdlib.h>
#include <string.h>

#include "llist.h"

int llistheadInit(int size, llisthead_t **l)
{
	*l = malloc(sizeof(llisthead_t));	
	if (NULL == *l)
		return -1;
	(*l)->head.prev = (*l)->head.next = &(*l)->head;
	(*l)->size = size;
	(*l)->head.data = NULL;
	
	return 0;
}

static void __insert(struct node_st *new, struct node_st *prev, struct node_st *next)
{
	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;
}

int llistInsert(llisthead_t *h, const void *data, int way)
{
	struct node_st *new;	

	if (way != LLISTINSERTHEAD && way != LLISTINSERTTAIL)
		return -1;

	new = malloc(sizeof(struct node_st));
	if (NULL == new)
		return -1;
	new->data = malloc(h->size);
	if (NULL == new->data) {
		free(new);
		return -1;
	}
	memcpy(new->data, data, h->size);
	if (way == LLISTINSERTHEAD)
		__insert(new, &h->head, h->head.next);
	else 
		__insert(new, h->head.prev, &h->head);

	return 0;
}

void llistTraval(const llisthead_t *h, pri_t p)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next)
		p(cur->data);
}

static struct node_st *__find(const llisthead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *cur;

	for (cur = h->head.next; cur != &h->head; cur = cur->next)
		if (!cmp(cur->data, key))
			return cur;
	return NULL;
}

// 查找
void *llistSearch(const llisthead_t *h, const void *key, cmp_t cmp){
	struct node_st *f;

	f = __find(h, key, cmp);
	if (NULL == f)
		return NULL;
	return f->data;
}

static void __delete(struct node_st *del)
{
	del->prev->next = del->next;
	del->next->prev = del->prev;
	del->prev = del->next = NULL;

	free(del->data);
	free(del);
}

// 删除
int llistDelete(llisthead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *f;

	f = __find(h, key, cmp);
	if (NULL == f)
		return -1; 
	__delete(f);	

	return 0;
}

// 摘除 == 删除结点前copy数据
int llistFetch(llisthead_t *h, const void *key, cmp_t cmp, void *data)
{
	struct node_st *f;

	f = __find(h, key, cmp);
	if (NULL == f)
		return -1; 
	memcpy(data, f->data, h->size);
	__delete(f);	
	
	return 0;
}

void llistDestroy(llisthead_t *h)
{
	struct node_st *cur;

	if (h->head.next != &h->head) {
		for (cur = (h->head.next)->next; ; cur = cur->next) {
			free(cur->prev->data);	
			free(cur->prev);
			if (cur == &h->head)
				break;
		}
	}
	free(h);
}




