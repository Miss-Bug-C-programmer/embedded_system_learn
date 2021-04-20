#include <stdio.h>

int main(void)
{
	int arr[10] = {3,2,1,7,8,9,4,5,6,0}; 
	int i, j;
	int t;

	// 直接插入排序
	// 选择带插入元素
	for (i = 1; i < 10; i++) {
		t = arr[i];
		// 比较有序区中的每一个元素	
		for (j = i-1; j >= 0; j--) {
			if (t > arr[j])
				arr[j+1] = arr[j];
			else
				break;
		}
		arr[j+1] = t;
	}

	for (i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

