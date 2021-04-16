#include <stdio.h>

// 函数体外定义的变量:全局变量(生存周期/作用域:定义开始到整个文件(进程)) 没有初始化，值一定是0
int g; // extern(默认)
/*
 修饰变量关键字
static:
	修饰全局变量，限制其只能在本文件中使用这个变量,不能被extern声明
	修饰函数,限制在本文件中调用
	修饰局部变量
extern全局变量声明
auto局部变量默认
register寄存器 
volatile 易失变量,防止编译优化
const 只读变量
 */

// 声明
int max2num(int a, int b);
extern void test(void);
int testStatic(void);
int main(void)
{
	// 函数内定义的变量---》局部变量(生存周期，作用域), 未初始化，值随机
	auto int a, b; // 默认
	int ret;
	int i = 1;
	int j = 6;
	int p, q;
	const int r = 10;

	r++;

	p = (i++) + (i++) + (i++);
	q = (j++) + (j++) + (j++);
	printf("i:%d, j:%d, p:%d, q:%d\n", i, j, p, q);

	// 参数的传参次序是至右向左
	printf("%d %d %d\n", i++, i+10, i++);

	g = 100;

	a = 10;
	b = -10;
	// 调用	
	ret = max2num(a, b);
	printf("%d\n", ret);
	printf("g:%d\n", g);

	test();

	printf("%d\n", testStatic());
	printf("%d\n", testStatic());
	printf("%d\n", testStatic());

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

int testStatic(void)
{
	// 局部静态变量,延长生命周期到整个文件，未初始化值为0
	static int var = 0; // 初始值一定为0

	var++;

	return var;
}



