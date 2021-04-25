#include <stdio.h>

void test(int n, int (*p)(int));
static int sumn(int n)
{
	if (n == 1)
		return 1;
	return n + sumn(n-1);
}

static int fibn(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fibn(n-1) + fibn(n-2);
}

int main(void)
{
	int num = 5;

	test(num, sumn);
	test(num, fibn);

	return 0;
}

void test(int n, int (*p)(int))
{
	printf("%d\n", p(n)); 
}



