#include <stdio.h>

int main(void)
{
	int num;	
	long res = 1;

	printf("请输入一个整型数:");
	scanf("%d", &num);

	for (; num > 0; num --) {
		res *= num; // res = res * num
	}
	printf("res:%ld\n", res);

	return 0;
}

