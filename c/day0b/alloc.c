#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *p;

	p = calloc(10, sizeof(char));
	if (NULL == p) {
		printf("空间申请失败\n");
	} else {
		strcpy(p, "hello");
		puts(p);
		p = realloc(p, 20); // 
		puts(p);
		strcat(p, "world");
		puts(p);
	}

	return 0;
}

