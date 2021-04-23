#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
动态整型数组 
 */

int addElement(int **arr, int *n, int elm);
void travalArray(const int *arr, int n);
int delArray(int **arr, int *n, int key);
int main(void)
{
	int *p = NULL;
	int n = 0;
	int i;

	for (i = 1; i <= 10; i++)
		addElement(&p, &n, i);

	travalArray(p, n);
	delArray(&p, &n, 5);
	travalArray(p, n);

	return 0;
}

/* 向数组中增加一个新的元素
arr:存储数组首地址指针变量的地址
*arr动态数组的首地址
n:存储数组成员个数变量的地址
elm:插入元素
return :
	0成功 -1失败
*/
int addElement(int **arr, int *n, int elm)
{
	*arr = realloc(*arr, (*n+1) * sizeof(int));
	if (NULL == *arr)
		return -1;
	(*arr)[*n] = elm;
	(*n)++;	

	return 0;
}

// 遍历整型数组
void travalArray(const int *arr, int n)
{
	int i;

	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
int delArray(int **arr, int *n, int key)
{
	// 找
	int i;

	for (i = 0; i < *n; i++) {
		if ((*arr)[i] == key)
			break;
	}
	if (i == *n)
		return -1;
	// i就是待删除元素的下标
#if 0
	for (; i < *n-1; i++) {
		(*arr)[i] = (*arr)[i+1];
	}
#endif
	memcpy(*arr+i, *arr+i+1, (*n-i-1)*sizeof(int));
	--*n;
	*arr = realloc(*arr, (*n) * sizeof(int));
	// if error

	return 0;
}



