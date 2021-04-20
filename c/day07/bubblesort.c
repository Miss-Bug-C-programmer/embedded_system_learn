#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N 20

int main(void)
{
	int arr[N] = {};
	int i, j;
	int tmp;

	srand(getpid());
	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;
	}
	// 冒泡排序
	for (i = 0; i < N-1; i++) { // 控制第几趟
		for (j = 0; j < N-i-1; j++) { // 每一趟要比较的元素下标范围
			if (arr[j] > arr[j+1]) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;	
			}
		}
	}

	for (i = 0; i < N; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

