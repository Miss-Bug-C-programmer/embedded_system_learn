/*
 已知1990.1.1是星期一,要求读入用户输入的90年后的日期(year/month)
打印其日历 
 */
#include <stdio.h>

int main(void)
{
	int year, month;	
	int i;
	int sumdays = 0;
	int firstday;

	do {
		printf("请输入1990后的任意日期(year/month):");
		scanf("%d/%d", &year, &month);
	} while (!(month > 0 && month < 13 && year >= 1990));

	// year.month.1是星期几?
	// 1990.1.1~year.month.1总天数 % 7
	for (i = 1990; i < year; i++) {
		sumdays += (i % 4 == 0 && i % 100 != 0 || i % 400 == 0) ? 366 : 365;
	}
	
	for (i = 1; i < month; i++) {
		if (i == 1 || i == 3 || i == 5 || i == 7 \
				|| i == 8 || i == 10 || i == 12)
			sumdays += 31;
		else if (i == 4 || i == 6 || i == 9 || i == 11)
			sumdays += 30;
		else
			sumdays += 28+(year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
	}
	sumdays += 1;
	firstday = sumdays % 7;
	printf("星期%d\n", firstday);

	return 0;
}

