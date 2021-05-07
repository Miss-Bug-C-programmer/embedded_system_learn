#include <stdio.h>
#include "lqueue.h"

int lqueueInit(int size, lqueue_t **lq)
{
	return llistheadInit(size, lq);
}

int lqueueEnq(lqueue_t *lq, const void *data)
{
	return llistInsert(lq, data, LLISTINSERTTAIL);
}

static int alwaysCmp(const void *data, const void *key)
{
	return 0;
}

int lqueueDeq(lqueue_t *lq, void *data)
{
	return llistFetch(lq, NULL, alwaysCmp, data);
}

int lqueueEmpty(const lqueue_t *lq)
{
	return llistEmpty(lq);
}

void lqueueDestroy(lqueue_t *lq)
{
	llistDestroy(lq);
}


