#include <stdio.h>

// 函数体外定义的变量:全局变量(生存周期/作用域:定义开始到整个文件(进程)) 没有初始化，值一定是0
int g; // extern(默认)
/*
 修饰变量关键字
static:
	修饰全局变量，限制其只能在本文件中使用这个变量,不能被extern声明
 */

// 声明
int max2num(int a, int b);
extern void test(void);
int main(void)
{
	// 函数内定义的变量---》局部变量(生存周期，作用域), 未初始化，值随机
	int a, b; 
	int ret;

	g = 100;

	a = 10;
	b = -10;
	// 调用	
	ret = max2num(a, b);
	printf("%d\n", ret);
	printf("g:%d\n", g);

	test();

	return 0;
}

// 定义
int max2num(int a, int b)
{
	int res;
	
	g ++;

	res = (a > b ? a : b)+1;

	return res;
}

