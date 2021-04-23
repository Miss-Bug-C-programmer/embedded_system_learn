#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *reverseString(const char *s);
int main(void)
{
	char *ret;

	ret = reverseString("i am embedded");
	puts(ret);

	free(ret);
	
	return 0;
}

char *reverseString(const char *s)
{
	// 堆heap:用户自己决定何时申请何时释放
	char *str = NULL;
	int i, j;

	i = strlen(s);
	str = (char *)malloc(i+1);

	i--;
	j = 0;
	while (i >= 0) {
		str[j++] = s[i--];	
	}
	str[j] = '\0';

	return str;
}

