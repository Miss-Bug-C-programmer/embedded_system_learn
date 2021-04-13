
// 读入一个年份，判断是否为闰年(能被4整除并且不能被100整除，或者能被400整除的)
#include <stdio.h>

int main(void)
{
	int year;

	printf("请输入一个年份:");
	scanf("%d", &year);

	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		printf("%d是闰年\n", year);
	else
		printf("%d是平年\n", year);

	return 0;
}

