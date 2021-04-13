#include <stdio.h>

int main(void)
{
	int a, b;
	int c;

	a = 10;
	b = 5;

	// 算数运算符+-*/%
	c = b % a;
	printf("c:%d\n", c);

	// 关系运算符 >= <= == != > < 
	printf("%d\n", a == b);
	printf("%d\n", a > b);

	// 位运算符 & | ^ ~ << >>
	c = a & b;
	printf("c:%d\n", c);
	c = a | b;
	printf("c:%d\n", c);
	c = a ^ b;
	printf("c:%d\n", c);
	c = ~a;
	printf("c:%d\n", c);

	c = a >> 2;
	printf("c=a>>2:%d\n", c);
	c = a << 2; //00000000...000 101000
	printf("c=a<<2:%d\n", c);

	// 逻辑运算符 && || !、
	printf("%d\n", a < b && b > c);
	printf("%d\n", a < b || b > c);
	printf("%d\n", !a);

	// 三目运算符 条件运算符 ?:
	c = a > b ? a + b : a - b;
	printf("c:%d\n", c);

	// 赋值运算符 = += -= *=
	// a = a + 1;
	a += 1;

	// 自增自减运算符 ++ --
	// a += 1;
	c = a ++;
	printf("a:%d, c:%d\n", a, c);

	c = ++a;
	printf("a:%d, c:%d\n", a, c);

	// 逗号运算符
	a = 10, b = 6;
	c = (a++, a+b, b++);
	printf("a:%d, b:%d, c:%d\n", a, b, c);

	// 强转运算符	
	a = 257; // 00...001 0000 0001
	char ch = (char)a;
	printf("%d\n", ch);
	
	float d = 1.0;
	ch = d + a;

	// 取地址运算符 &
	// 取值 *
	printf("%d\n", *&a);

	return 0;
}





