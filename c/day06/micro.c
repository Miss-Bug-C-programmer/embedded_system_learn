#include <stdio.h>

/*
 gcc处理四个步骤：
 	1.预处理(-E):#开头
		#include 头文件展开
		#define	宏的替换
	2.编译(-S):c代码翻译成汇编
	3.汇编(-c):汇编代码生成机器码
	4.链接:动态链接库---->生成二进制文件
 */

// 宏---》预处理指令
#define N	10
// 宏函数
#define MAX2NUM(a, b) \
	(a) > (b) ? (a) : (b)
#define MUL2NUM(a, b) (a) * (b)

// 获取变量a类型
#define SWAP2NUM(a, b) \
	do {\
		typeof(a) c;\
		c = (a);\
		(a) = (b);\
		(b) = c;\
	} while(0)

#define HELLO

int main(void)
{
	int i;
	int m, n;

// 条件编译
#ifndef HELLO
	for (i = 0; i < N; i++) {
		printf("*");
	}
#endif
	printf("\n");

	m = 10;
	n = 20;
#if 0
	printf("%d\n", MAX2NUM(m, n));
#endif
	printf("%d\n", MUL2NUM(m+2, n+10));
	// (m+2)*(n+10)

	SWAP2NUM(m, n);
	printf("m:%d, n:%d\n", m, n);

	return 0;
}

