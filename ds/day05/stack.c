#include <stdlib.h>
#include <string.h>
#include "stack.h"

int stackInit(int size, int capcity, stack_t **s)
{
	*s = malloc(sizeof(stack_t));
	if (NULL == *s)
		return -1;
	(*s)->bottom = (*s)->top = calloc(capcity, size);
	if ((*s)->bottom == NULL) {
		free(*s);
		return -1;
	}
	(*s)->size = size;
	(*s)->capacity = capcity;

	return 0;
}

int stackIsEmpty(const stack_t *s)
{
	return s->bottom == s->top;
}

int stackIsFull(const stack_t *s)
{
	return ((char *)s->top - (char *)s->bottom) / s->size == s->capacity;
}

int push(stack_t *s, const void *data)
{
	if (stackIsFull(s))
		return -1;
	memcpy(s->top, data, s->size);
	s->top = (char *)s->top + s->size;

	return 0;
}

int pop(stack_t *s, void *data)
{
	if (stackIsEmpty(s))
		return -1;
	s->top = (char *)s->top - s->size;
	memcpy(data, s->top, s->size);

	return 0;
}

void stackDestroy(stack_t *s)
{
	free(s->bottom);
	free(s);
}

