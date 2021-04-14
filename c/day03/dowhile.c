#include <stdio.h>

int main(void)
{
	int month;

	do {
		scanf("%d", &month);
	} while (month < 1 || month > 12);

	return 0;
}

