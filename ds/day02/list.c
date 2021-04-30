#include <stdlib.h>
#include <string.h>

#include "list.h"

int listheadInit(int size, listhead_t **l)
{
	*l = malloc(sizeof(listhead_t));
	if (NULL == *l)
		return -1;
	(*l)->node.data = NULL;
	(*l)->node.next = &(*l)->node;
	(*l)->size = size;

	return 0;
}

static void __insert(struct node_st *new, struct node_st *next, struct node_st *prev)
{
	new->next = next;
	prev->next = new;
}

int listInsert(listhead_t *h, const void *data, int way)
{
	struct node_st *new;	
	struct node_st *cur;

	new = malloc(sizeof(struct node_st));
	if (NULL == new)
		return -1;
	new->data = malloc(h->size);
	if (NULL == new->data) {
		free(new);
		return -1;
	}
	memcpy(new->data, data, h->size);

	if (way == HEADINSERT) {
		__insert(new, h->node.next, &h->node);
	} else if (way == TAILINSERT){
		for (cur = h->node.next; cur->next != &h->node; cur = cur->next)
			;
		__insert(new, &h->node, cur);	
	} else {
		free(new->data);
		free(new);
		return -1;
	}

	return 0;
}

void listTraval(const listhead_t *h, pri_t p)
{
	struct node_st *cur = NULL;	

	for (cur = h->node.next; cur != &h->node; cur=cur->next)
		p(cur->data);
}

void listDestroy(listhead_t *h)
{
	struct node_st *cur, *next;		

	cur = h->node.next;
	next = cur->next;
	while (cur != &h->node) {
		free(cur->data);	
		free(cur);
		cur = next;
		next = cur->next;
	}
	free(h);
}

// 前驱
static struct node_st *__find(const listhead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *prev, *cur;	

	prev = &h->node;
	cur = prev->next;
	while (cur != &h->node) {
		if (!cmp(cur->data, key))
			return prev;
		prev = cur;
		cur = cur->next;
	}

	return NULL;
}

void *listSearch(const listhead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *prev;

	prev = __find(h, key, cmp);
	if (prev == NULL)
		return NULL;
	return prev->next->data;
}

// 删除
int listDelete(listhead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *prev, *del;	

	prev = __find(h, key, cmp);
	if (NULL == prev)
		return -1;
	del = prev->next;
	prev->next = del->next;
	del->next = NULL;
	free(del->data);
	free(del);

	return 0;
}

// 摘除 == 删除结点前copy数据
int listFetch(listhead_t *h, const void *key, cmp_t cmp, void *data)
{
	struct node_st *prev, *del;	

	prev = __find(h, key, cmp);
	if (NULL == prev)
		return -1;
	del = prev->next;
	prev->next = del->next;
	del->next = NULL;

	memcpy(data, del->data, h->size);

	free(del->data);
	free(del);

	return 0;


}



