#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void myqsort(int *arr, int nmemb);
int main(int argc, char *argv[])
{
	int *p;
	int i, j;
	// ./a.out 87723459
	if (argc < 2)	
		return 1;
	
	p = calloc(strlen(argv[1]), sizeof(int));
	if (NULL == p)
		return 1;
	for (i = 0; argv[1][i]; i++) {
		p[i] = argv[1][i] - '0';
	}
	printf("[%d]debug...\n", __LINE__);
	myqsort(p, i);
	printf("[%d]debug...\n", __LINE__);

	for (j = 0; j < i; j++)
		printf("%d ", p[j]);
	printf("\n");
	free(p);

	return 0;
}

// 分区
static int partition(int *arr, int low, int high)
{
	// 标兵
	int key = arr[low];

	while (low < high) {
		while (low < high && key < arr[high])	
			high--;
		if (low < high) {
			arr[low++] = arr[high];
		}
		while (low < high && key >= arr[low])
			low++;
		if (low < high) {
			arr[high--] = arr[low];
		}
	}
	arr[low] = key;

	return low;
}

static void _myqsort(int *arr, int low, int high)
{
	int pos;

	if (low >= high)
		return ;

	pos = partition(arr, low, high);
//	printf("pos:%d, value:%d\n", pos, arr[pos]);
//	sleep(1);
	_myqsort(arr, 0, pos-1);
	_myqsort(arr, pos+1, high);
}

void myqsort(int *arr, int nmemb)
{
	_myqsort(arr, 0, nmemb-1);	
}

