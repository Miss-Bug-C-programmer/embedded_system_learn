/*
 已知1990.1.1是星期一,要求读入用户输入的90年后的日期(year/month)
打印其日历 
 */
#include <stdio.h>

// 声明函数:返回值类型 函数名(参数列表类型);
int isLeap(int y);
int dayOfMonth(int month, int year);

int main(void)
{
	int year, month;	
	int i;
	int sumdays = 0;
	int firstday;
	int monthdays;

	do {
		printf("请输入1990后的任意日期(year/month):");
		scanf("%d/%d", &year, &month);
	} while (!(month > 0 && month < 13 && year >= 1990));

	// year.month.1是星期几?
	// 1990.1.1~year.month.1总天数 % 7
	for (i = 1990; i < year; i++) {
		if (isLeap(i))
			sumdays + =366;
		else
			sumdays += 365;
	}
	
	for (i = 1; i < month; i++) {
		// 调用
		sumdays += dayOfMonth(i, year);
	}
	sumdays += 1;
	firstday = sumdays % 7;
	// printf("星期%d\n", firstday);

	monthdays = dayOfMonth(month, year);
		
	// 打印日历
	printf("       %d月%d年\n", month, year);
	printf("日 一 二 三 四 五 六\n");
	// 空格
	for (i = 0; i < firstday; i++)
		printf("   ");
	for (i = 1; i <= monthdays; i++) {
		printf("%2d%c", i, (i+firstday) % 7 ? ' ':'\n');	
	}
	printf("\n");

	return 0;
}

/*
 判断是否为闰年
q1:哪一年--->所需条件--->形参列表
q2:得到结果--->回馈--->返回值
函数:
	组成部分:参数列表，返回值，函数名, 函数体
函数的定义
 */
int isLeap(int y)
{
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

/*
 给定年月，求出有多少天
 */
int dayOfMonth(int month, int year)
{
	int res = 0;

	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			res = 31;
			break;
		case 4: case 6: case 9: case 11:
			res = 30;
			break;
		case 2:
			// 函数的调用:函数名(参数值)
			res = 28 + isLeap(year); // ！！！！值传递
			break;
		default:
			break;
	}

	return res;
}







