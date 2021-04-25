#include <stdio.h>
#include <string.h>
/*
写一个接口:将字符串转换为整型
"254"--->254

 模拟一下四则运算
 ./a.out 1 + 2
 1+2=3
 ./a.out 182 x 2
 1*2=2
 */

int myatoi(const char *p);
int main(int argc, char *argv[]) // char **argv / char argv[][]
{
	int left, right;
	int res;;

	if (argc < 4)
		return 1;

	left = myatoi(argv[1]);
	right = myatoi(argv[3]);

	if (!strcmp(argv[2], "+"))
		res = left + right;
	else if (!strcmp(argv[2], "-"))
		res = left - right;
	else if (!strcmp(argv[2], "x"))
		res = left * right;
	else if (!strcmp(argv[2], "/"))
		res = left / right;
	else {
		printf("没有此运算符\n");
		return 1;
	}

	printf("%d %s %d = %d\n", left, argv[2], right, res);

	return 0;
}

int myatoi(const char *p)
{
	int res = 0;

	// "123"
	while (*p) {
		res = res * 10 + (*p - '0');
		p++;
	}

	return res;
}

