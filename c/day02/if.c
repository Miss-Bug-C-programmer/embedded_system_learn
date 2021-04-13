#include <stdio.h>

int main(void)
{
	int num;

	// 读入
	printf("请输入一个整型变量:");
	scanf("%d", &num);

	if (num % 2 == 0) {
		printf("%d是一个偶数\n", num);
		printf("太棒了！\n");
	} else {
		printf("%d是一个奇数\n", num);
	}

	return 0;
}

