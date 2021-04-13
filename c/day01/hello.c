#include <stdio.h>
/*
#开头---》预处理指令
#include 头文件的包含
	头文件中包含函数的声明，类型的定义
	处理:将其展开
 */
/*
 入口函数
 */
int main(void)
{
	/*
	 基本数据类型
	 	有符号(signed) 无符号(unsigned)
	 	整型:short(2) int(4) long(8) (long long)
		字符:char
		实型:float double long double
		空类型:void
		复合类型:struct union enum

		计算机存储单位:
			位 bits --->1字节(bytes)=8比特
			--->1k=1024bytes--->1M=1024k---->1G=1024M
		进制:
			二进制(1 0)
			八进制(0~7)
			十进制(0~9)
			十六进制(0~9,a~f)
	 */
	// 变量定义
	int var;
	// 初始化
	int n = 10;
	char ch = '9'; // ascii
	
	// 赋值
	var = 100;
	/*
	 标识符:变量名，函数名，类型名
	 由字母数字下划线组成，数字不开头，并避开c关键字
	 */

	printf("var的值是%d\n", var);
	printf("hello world\n");

	// sizeof(类型)--->计算字节个数
	printf("%ld\n", sizeof(short));
	printf("%ld\n", sizeof(int));
	printf("%ld\n", sizeof(long));
	printf("%ld\n", sizeof(long long));

	printf("%ld\n", sizeof(float));
	printf("%ld\n", sizeof(double));
	printf("%ld\n", sizeof(long double));

	return 0;
}

