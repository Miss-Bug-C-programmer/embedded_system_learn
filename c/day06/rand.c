#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define N	5

int main(void)
{
	int arr[N] = {};
	int i;

	// srand(time(NULL));
	srand(getpid()); // 进程号

	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;
		printf("%d\n", arr[i]);
	}

	return 0;
}

