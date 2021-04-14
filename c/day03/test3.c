#include <stdio.h>

int main(void)
{
	int i;
	int cnt = 0;

	for (i = 1; i <= 100; i ++) {
		if (i % 3 == 0 && i % 5 == 0)
			cnt ++;	
	}	
	printf("cnt:%d\n", cnt);

	return 0;
}
