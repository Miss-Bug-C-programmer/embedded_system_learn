#include <stdio.h>

#include "lqueue.h"

int main(int argc, char *argv[])
{
	lqueue_t *s;
	int i;
	char ch;

	if (argc < 2)
		return 1;

	lqueueInit(sizeof(char), &s);

	for (i = 0; argv[1][i]; i++)
		lqueueEnq(s, argv[1]+i);
	while (!lqueueEmpty(s)) {
		lqueueDeq(s, &ch);
		putchar(ch);
	}
	putchar('\n');

	lqueueDestroy(s);

	return 0;
}

