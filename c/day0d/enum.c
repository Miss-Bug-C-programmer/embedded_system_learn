#include <stdio.h>

enum {LEFT=1, RIGHT, UP=8, DOWN};

int main(void)
{
	int menu;

	scanf("%d", &menu);

	switch (menu) {
		case LEFT:
			printf("left...\n");
			break;
		case RIGHT:
			printf("right...\n");
			break;
		case UP:
			printf("up...\n");
			break;
		case DOWN:
			printf("down...\n");
			break;
		default:
			break;
	}

	return 0;
}
