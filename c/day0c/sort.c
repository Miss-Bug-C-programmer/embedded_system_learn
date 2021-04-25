#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 任意类型数组排序	 
 */

void mysort(void *arr, int nmembs, int size, int (*cmp)(const void *, const void *));
static int cmp_int(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d2 - *d1;
}

static int cmp_char(const void *data1, const void *data2)
{
	const char *d1 = data1;
	const char *d2 = data2;

	return *d2 - *d1;
}

static int cmp_str(const void *data1, const void *data2)
{
	char *const*d1 = data1;
	char *const*d2 = data2;

	return strcmp(*d2, *d1);
}

int main(int argc, char **argv)
{
	int arr[10] = {3,2,1,6,7,9,4,2,8};
	char p[] = "hello world";
	
	mysort(arr, 10, sizeof(int), cmp_int);
	for (int i = 0; i < 10; i++)
		printf("%d ",arr[i]);
	printf("\n");

	mysort(p, strlen(p), sizeof(char), cmp_char);
	puts(p);

	mysort(argv, argc, sizeof(char *), cmp_str);
	for (int i = 0; i < argc; i++ )
		puts(argv[i]);

	return 0;
}


void mysort(void *arr, int nmembs, int size, int (*cmp)(const void *, const void *))
{
	int i, j;	

	char *tmp = malloc(size);

	for (i = 0; i < nmembs-1; i++) {
		for (j = 0; j < nmembs-i-1; j++) {
			if (cmp((char *)arr+size*j, \
					(char *)arr+(j+1)*size)	> 0) {
				memcpy(tmp, (char *)arr+size*j, size);	
				memcpy((char *)arr+size*j, \
						(char *)arr+size*(j+1), size);
				memcpy((char *)arr+size*(j+1), tmp, size);
			}
		}
	}	

	free(tmp);
}



