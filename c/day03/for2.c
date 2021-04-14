#include <stdio.h>

int main(void)
{
	int n;
	int i, j;
	int flag = 1;
	int cnt = 0;

	// 统计1~100之间奇数有多少质数

	for (j = 1; j < 100; j++) {
		if (j % 2 == 0)
			continue; // 终止本次循环,继续下一次
		flag = 1;
		for (i = 2; i < j; i++) {
			if (j % i == 0) {
				flag = 0;
				break; // 终止掉循环
			}
		}
		if (flag)
			cnt++;
	}

	return 0;
}

