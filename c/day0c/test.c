#include <stdio.h>
#include <stdlib.h>
/*
 实现从终端读入一行字符串
 */

// 空间申请以10字节为单位
#define SIZE	10

int mygetline(char **ptr, size_t *n);

int main(void)
{
	char *p = NULL;
	size_t n = 0;
	int size;

	size = mygetline(&p, &n);
	puts(p);

	printf("n:%ld, size:%d\n", n, size);

	free(p);

	return 0;
}

int mygetline(char **ptr, size_t *n)
{
	int ch;
	int i;
	// hello
	i = 0;
	while (1) {
		// 有存储空间容纳所读取的字符
		if (i >= *n) {
			*n += SIZE;
			*ptr = realloc(*ptr, *n);	
			if (NULL == *ptr)
				return -1;
		}
		ch = getchar();
		(*ptr)[i] = ch;
		if ((*ptr)[i] == '\n') {
			(*ptr)[i] = '\0';
			break;
		}
	
		i++;
	}

	return i;
}







