#include <stdlib.h>
#include <string.h>

#include "seq.h"

int seqlistInit(int size, int capacity, seqlist_t **sl)
{
	*sl = malloc(sizeof(seqlist_t));
	if (NULL == *sl)
		return -1;
	(*sl)->arr = calloc(capacity, size);
	if (NULL == (*sl)->arr) {
		free(*sl);
		return -1;
	}
	(*sl)->size = size;
	(*sl)->capacity = capacity;
	(*sl)->nmembs = 0;

	return 0;
}

int seqlistAdd(seqlist_t *sl, const void *data)
{
	if (sl->nmembs == sl->capacity)
		return -1;
	memcpy((char *)sl->arr+sl->size*sl->nmembs, data, sl->size);
	sl->nmembs ++;
	
	return 0;
}

void seqlistTraval(const seqlist_t *sl, pri_t pri)
{
	int i;

	for (i = 0; i < sl->nmembs; i++) {
		pri((char *)sl->arr+i*sl->size);
	}
}

void seqlistDestroy(seqlist_t *sl)
{
	free(sl->arr);
	free(sl);
}

int seqlistDelete(seqlist_t *sl, const void *key, cmp_t cmp)
{
	int i;

	for (i = 0; i < sl->nmembs; i++) {
		if (!cmp((char *)sl->arr+i*sl->size, key)) {
			break;	
		}
	}
	if (i == sl->nmembs)
		return -1;
	memcpy((char *)sl->arr+i*sl->size, \
			(char *)sl->arr+(i+1)*sl->size, \
			(sl->nmembs-(i+1))*sl->size);
	sl->nmembs--;

	return 0;
}



