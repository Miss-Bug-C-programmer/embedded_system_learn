#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf env;

static int div2num(int a, int b)
{
	if (b == 0)
		// 跳转到main 重新读入变量
		longjmp(env, 1);

	return a / b;
}

int main(void)
{
	int num1, num2;

	if (setjmp(env) == 0)
		printf("请输入两个整型变量:");
	else
		printf("请重新输入:");
	scanf("%d%d", &num1, &num2);

	printf("res:%d\n", div2num(num1, num2));

	exit(0);
}

