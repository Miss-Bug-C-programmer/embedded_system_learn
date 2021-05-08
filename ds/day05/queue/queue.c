#include <stdlib.h>

#include "queue.h"

int queueInit(int size, int capacity, queue_t **q)
{
	*q = malloc(sizeof(queue_t));
	if (NULL == *q)
		return -1;
	(*q)->base = calloc(capacity, size);
	if (NULL == (*q)->base) {
		free(*q);
		return -1;
	}
	(*q)->front = (*q)->tail = 0;
	(*q)->size = size;
	(*q)->capacity = capacity;
	
	return 0;
}

int queueIsEmpty(const queue_t *q)
{
	return q->front == q->tail;
}

int queueIsFull(const queue_t *q)
{
	return (q->tail+1) % q->capacity == q->front;
}

int enq(queue_t *q, const void *data)
{
	if (queueIsFull(q))
		return -1;
	memcpy((char *)q->base+q->tail*q->size, data, q->size);
	q->tail = (q->tail + 1) % q->capacity;

	return 0;
}

int deq(queue_t *q, void *data)
{
	if (queueIsEmpty(q))
		return -1;
	memcpy(data, (char *)q->base + q->front*q->size, q->size);
	q->front = (q->front+1) % q->capacity;

	return 0;
}

void queueDestroy(queue_t *q)
{
	free(q->base);
	free(q);
}

