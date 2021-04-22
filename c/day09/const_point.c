#include <stdio.h>

int main(void)
{
	char str[] = "night";
	const char *p = str; // 常量(的)指针:指针存储空间值是只读的
	// char const *p
	char *const q = str; // 指针(的)常量

	// str[0] = 'h'; 不受限制
	// *p = 'h'; *p只读
	p++; // 允许

	*q = 'h';
	// q++; q只读的

	return 0;
}

