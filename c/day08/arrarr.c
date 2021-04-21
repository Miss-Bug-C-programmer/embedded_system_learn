#include <stdio.h>

/*
 打印杨辉三角
 1
 1 1
 1 2 1
 1 3 3 1
 1 4 6 4 1
 */

#define N 10

int main(void)
{
#if 0
	int arr[2][3] = {
		{1,2,3},
		{11,22,33}
	};
	int i, j;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
#endif
	int arr[N][N] = {};
	int i, j;
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (j == 0 || i == j) {
				arr[i][j] = 1;
			} else {
				if (i > 0 && j < i) {
					arr[i][j] = arr[i-1][j] + arr[i-1][j-1];
				}
			}
		}
	}

	// 遍历
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (j <= i) {
				printf("%-4d", arr[i][j]);	
			}
		}
		printf("\n");
	}

	return 0;
}


