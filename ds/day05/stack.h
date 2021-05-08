#ifndef __STACK_H
#define __STACK_H

typedef struct {
	void *bottom;
	void *top;
	int size;
	int capacity;
}stack_t;

int stackInit(int size, int capcity, stack_t **s);
int stackIsEmpty(const stack_t *s);
int stackIsFull(const stack_t *s);
int push(stack_t *s, const void *data);
int pop(stack_t *s, void *data);
void stackDestroy(stack_t *s);

#endif

