#include <stdio.h>

int main(void)
{
	int row;
	int i, j;

	scanf("%d", &row);

	// 正方形
	for (i = 0; i < row; i++) {
		for (j = 0; j < row; j++)
			printf("* ");
		printf("\n");
	}

	// 四边形
	for (i = 0; i < row; i++) {
		// 空格
		for (j = 0; j < i; j++)
			printf("  ");
		for (j = 0; j < row; j++)
			printf("* ");
		printf("\n");
	}
	
	// 三角
	printf("三角形\n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < row-i-1; j++)
			printf("  ");
		for (j = 0; j < 2 * i + 1; j++)
			printf("* ");
		printf("\n");
	}



	return 0;
}

