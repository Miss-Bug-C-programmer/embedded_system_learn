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

