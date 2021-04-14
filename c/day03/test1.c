#include <stdio.h>

int main(void)
{
	int res = 0;
	int i;

	for (i = 1; i < 100; i++) {
		if (i % 2) {
			res += i;
		}
	}
	printf("res:%d\n", res);

	return 0;
}

