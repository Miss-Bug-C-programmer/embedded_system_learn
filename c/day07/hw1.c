#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N	20

int main(void)
{
	int i;
	int arr[N];
	int max_i, min_i;
	int tmp;

	srand(getpid());
	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;		
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	max_i = min_i = 0;
	for (i = 1; i < N; i++) {
		if (arr[i] > arr[max_i])
			max_i = i;
		if (arr[i] < arr[min_i])
			min_i = i;
	}
	tmp = arr[max_i];	
	arr[max_i] = arr[min_i];
	arr[min_i] = tmp;

	for (i = 0; i < N; i++)
		printf("arr[%d]:%d\n", i, arr[i]);

	return 0;
}


