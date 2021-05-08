#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

char *changeDec(int num);
int main(int argc, char *argv[])
{
	char *res;

	if (argc < 2)
		return 1;

	res = changeDec(atoi(argv[1]));
	puts(res);
	
	free(res);
	
	return 0;
}

char *changeDec(int num)
{
	stack_t *s;	
	char ch;
	char *ret = NULL;
	int i;

	if (num <= 0)
		return NULL;

	stackInit(sizeof(char), 32, &s);

	while (num) {
		ch = num % 2 + '0';
		push(s, &ch);	
		num /= 2;
	}

	i = 1;
	while (!stackIsEmpty(s)) {
		pop(s, &ch);
		ret = realloc(ret, (i+1)*sizeof(char));
		ret[i-1] = ch;
		i++;
	}
	ret[i-1] = '\0';
	stackDestroy(s);

	return ret;
}







