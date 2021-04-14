#include <stdio.h>

/*
	for (循环变量初始化; 循环条件; 循环变量的改变) {
		结构体语句;
	}
 */
/*
 练习:
 	1.将1-100之间的所有的奇数累加求和
	2.读入一个整型变量，判断其是否是一个质数(除了1和本身不能被其他数整除的数)
 */
int main(void)
{
	int n = 10;
	int res = 0;
	int i;

	for (i = 0; i <= n; i++) {
		res = res + i;
		// res += i;
	}

	printf("%d的前n项和为%d\n", n, res);

	return 0;
}
  
