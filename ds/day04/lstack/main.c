#include <stdio.h>

#include "lstack.h"

int main(int argc, char *argv[])
{
	lstack_t *s;
	int i;
	char ch;

	if (argc < 2)
		return 1;

	lstackInit(sizeof(char), &s);

	for (i = 0; argv[1][i]; i++)
		lstackPush(s, argv[1]+i);
	while (!lstackEmpty(s)) {
		lstackPop(s, &ch);
		putchar(ch);
	}
	putchar('\n');

	lstackDestroy(s);

	return 0;
}

