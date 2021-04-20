#include <stdio.h>

int main(void)
{
	int arr[] = {3,2,1,4,6,9,7,8,2};
	int selecti;
	int i, j;
	int tmp;

	// 选择排序
	// sizeof(数组名)--->整个数组占字节个数
	for (i = 0; i < sizeof(arr) / sizeof(int) - 1; i++)	{
		selecti = i; // 选择元素下标值
		for (j = i+1; j < sizeof(arr) / sizeof(int); j++) {
			if (arr[j] < arr[selecti]) {
				selecti = j;
			}
		}
		if (selecti != i) {
			tmp = arr[selecti];
			arr[selecti] = arr[i];
			arr[i] = tmp;
		}
	}

	for (i = 0; i < sizeof(arr) / sizeof(int); i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

