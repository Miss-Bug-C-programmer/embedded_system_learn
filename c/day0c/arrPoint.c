#include <stdio.h>

int main(void)
{
	int arr[2][3] = {
		{1,2,3},
		{4,5,6}
	};
	int (*p)[3] = arr; // 数组指针
	int i, j;
	
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}

	return 0;
}
