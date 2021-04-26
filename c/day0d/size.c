#include <stdio.h>

struct test_st {
	char a;
	int c;
	short b;
	long d;
};

int main(void)
{
	struct test_st var;
	printf("sizeof(var):%ld\n", sizeof(var));
	printf("%p, %p, %p, %p\n", &var.a, &var.c, &var.b, &var.d);

	return 0;
}
