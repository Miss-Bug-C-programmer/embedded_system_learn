#include <stdio.h>

union test_un {
	int a;
	char b;
	long c;
};

int main(void)
{
	// 大端存储:低字节存高地址，高字节存低地址
	// 小端存储:低字节存低地址，高字节存高地址
	union test_un u;	
	u.a = 0x12345678;
	u.b = 0x98;
	printf("u.a:%#x\n", u.a);
	printf("u.c:%#x\n", u.c);

	return 0;
}

