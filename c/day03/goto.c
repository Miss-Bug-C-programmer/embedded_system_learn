#include <stdio.h>

int main(void)
{
	int n = 10;
	int res = 0;

LOOP:
	res += n;
	n--;
	if (n > 0)
		goto LOOP; // 无条件跳转，不能跨函数

	return 0;
}

