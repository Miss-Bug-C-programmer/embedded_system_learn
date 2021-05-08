#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct {
	void *base;
	int front;
	int tail;
	int size;
	int capacity;
}queue_t;

// 
int queueInit(int size, int capacity, queue_t **q);
int queueIsEmpty(const queue_t *q);
int queueIsFull(const queue_t *q);
int enq(queue_t *q, const void *data);
int deq(queue_t *q, void *data);
void queueDestroy(queue_t *q);

#endif

