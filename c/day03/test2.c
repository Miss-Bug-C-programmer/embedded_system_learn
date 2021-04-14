#include <stdio.h>

int main(void)
{
	int n;
	int i;
	int flag = 1;

	printf("输入n:");
	scanf("%d", &n);

	for (i = 2; i < n; i++) {
		if (n % i == 0) {
			flag = 0;
		}
	}
	if (flag)
		printf("%d是一个质数\n", n);
	else
		printf("%d不是质数\n", n);

	return 0;
}

