/*
 定义一个能容纳10个整型变量的数组，
 从终端读入10个整型数并存储到数组中，
 求出最大值和最小值
 */
#include <stdio.h>

int main(void)
{
	int arr[10] = {};
	int i;
	int max, min;

	for (i = 0; i < 10; i++) {
		printf("请输入第%d个整型数:", i+1);
		scanf("%d", arr+i); // &arr[i]
	}
	
	max = min = arr[0];	
	for (i = 1; i < 10; i++) {
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	
	printf("max:%d, min:%d\n", max, min);

	return 0;
}

