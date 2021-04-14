#include <stdio.h>
/*
 while (循环条件) {
 	循环体;
 }
 
 */
int main(void)
{
	int n;
	int res = 0;

	scanf("%d", &n);

	// 15329 // 求n的倒叙数 123--->321
	while (n > 0) {
		res = res*10 + n % 10;
		n /= 10;
	}

	return 0;
}

