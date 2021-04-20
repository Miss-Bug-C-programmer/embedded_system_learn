#include <stdio.h>

#define N	10

static int isPrimer(int n);
int main(void)
{
	int arr[N];
	int i;

	for (i = 0; i < N; i++) {
		scanf("%d", arr+i);
	}

	for (i = 0; i < N; i++) {
		if (isPrimer(arr[i]))
			printf("%d is a primer\n", arr[i]);
	}

	return 0;
}

static int isPrimer(int n)
{
	int i;

	for (i = 2; i < n; i++) {
		if (n % i == 0)
			break;
	}
	if (i == n)
		return 1;
	return 0;
}

