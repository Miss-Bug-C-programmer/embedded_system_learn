#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void test(void)
{
	printf("%s is called", __FUNCTION__);
	exit(0);
	// _exit(0);
}

static void handler1(void)
{
	printf("register a function:%s to be called\n", \
			__FUNCTION__);
}

static void handler2(void)
{
	printf("register a function:%s to be called\n", \
			__FUNCTION__);
}

static void handler3(void)
{
	printf("register a function:%s to be called\n", \
			__FUNCTION__);
}

int main(void)
{
	atexit(handler1);
	atexit(handler2);
	atexit(handler3);

	printf("%s is called", __FUNCTION__);
	test();
	printf("%s will be end\n", __FUNCTION__);

	exit(0);
}

