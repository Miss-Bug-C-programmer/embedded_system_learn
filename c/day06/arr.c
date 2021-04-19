#include <stdio.h>
/*
 数组:相同类型元素的集合
 定义:
 	type name[nmemb];
 */
int main(void)
{
	// 定义
	int arr[5]; // 五个相同类型的局部变量
	int i;
	// 初始化
	int arr2[3] = {1, 10};

	// 取得数组中每一个元素
	for(i = 0; i < 5; i++) {
		arr[i] = i+1;
	}

	// 遍历
	for (i = 0; i < 5; i++) {
		printf("%p\n", arr + i);
		printf("%d\n", arr[i]);
		// *(arr+i)
	}

	return 0;
}

