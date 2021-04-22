#include <stdio.h>
#include <string.h>

#define N	10

int main(void)
{
	char arr[N] = {};
	int i, j;

	for (i = 0; i < N-1; i++) {
		arr[i] = getchar();
		if (arr[i] == '\n') {
			arr[i] = '\0';
			break;
		}
	}

	for (i = 0, j = strlen(arr)-1; i < j; i++, j--)	{
		if (arr[i] != arr[j])
			break;
	}
	if (i >= j) {
		printf("%s是一个对称字符串\n", arr);
	} else {
		printf("%s不是一个对称字符串\n", arr);
	}

	return 0;
}

