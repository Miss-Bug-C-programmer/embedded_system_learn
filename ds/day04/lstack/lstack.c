#include "lstack.h"
#include <stdio.h>

int lstackInit(int size, lstack_t **ls)
{
	return llistheadInit(size, ls);
}

int lstackPush(lstack_t *ls, const void *data)
{
	return llistInsert(ls, data, LLISTINSERTHEAD);
}

static int alwayCmp(const void *data, const void *key)
{
	return 0;
}

int lstackPop(lstack_t *ls, void *data)
{
	return llistFetch(ls, NULL, alwayCmp, data);
}

int lstackEmpty(const lstack_t *ls)
{
	return llistEmpty(ls);
}

void lstackDestroy(lstack_t *ls)
{
	llistDestroy(ls);
}

