#include <stdio.h>

/*
 指针:存储地址变量
 定义:
 	type *name; // name指针变量,类型是type * 
	type由所存储的地址类型决定
	name占多大存储空间在64os 8bytes
 */

void swap2num(int *p1, int *p2);
void maxminarr(int *arr, int n, int *max, int *min);
int main(void)
{
	int m, n;
	char *p = "good morning"; // 字符串常量的首地址存储到指针变量p
	char str[] = "hello world"; // 将字符串中的每一个字符相应的存储到数组的每一个元素，变量
	int i = 0;
	int arr[] = {10, 20, 33, 1, -1, 23};

	m = 10;
	n = 20;

	swap2num(&m, &n);
	printf("m:%d, n:%d\n", m, n);

	// 最大最小值
	maxminarr(arr, sizeof(arr) / sizeof(int), &m, &n);
	printf("最大:%d, 最小:%d\n", m, n);

	return 0;
}

// 求字符串长度
int mystrlen(char *p)
{
	int len = 0;

	while (*p) {
		len ++;	
		p++;
	}

	return len;
}

// 两个整型变量的交换
void swap2num(int *p1, int *p2)
{
	int t;

	t = *p1;
	*p1 = *p2;
	*p2 = t;
}

// 求出给定整型数组中的最大最小值返回 --->参数回填
void maxminarr(int *arr, int n, int *max, int *min)
{
	int i;

	*max = *min= arr[0];
	for (i = 1; i < n; i++) {
		if (arr[i] > *max)
			*max = arr[i];
		if (arr[i] < *min)
			*min = arr[i];
	}
}



