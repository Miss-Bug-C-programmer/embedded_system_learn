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

int listheadInit(int size, listhead_t **l);

int listInsert(listhead_t *h, const void *data, int way);

void listTraval(const listhead_t *h, pri_t p);

void listDestroy(listhead_t *h);

#endif

