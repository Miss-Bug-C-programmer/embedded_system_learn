#include <stdio.h>

int fib(int n);
int sumn(int n);
int main(void)
{
	for (int i = 1; i <= 20; i++)
		printf("%d\n", fib(i));

	return 0;
}

int sumn(int n)
{
	if (n == 0)
		return 0;
	return n + sumn(n-1);
}

// 斐波那契数列:1 1 2 3 5 8 13......
int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fib(n-1) + fib(n-2);
}






