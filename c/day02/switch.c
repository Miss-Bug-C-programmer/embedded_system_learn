#include <stdio.h>

int main(void)
{
	int score;

	scanf("%d", &score);

	switch (score / 10) {
		case 10:
			// printf("A\n");
			// break;
		case 9:
			printf("A\n");
			break;
		case 8:
			printf("B\n");
			break;
		case 7:
			printf("C\n");
			break;
		case 6:
			printf("D\n");
			break;
		default:
			printf("不合格\n");
			break;
	}

	return 0;
}

