#include <stdio.h>

#include "tree.h"

static int cmpInt(const void *data, const void *node)
{
	const int *d = data;
	const int *n = node;

	return *d - *n;	
}

static void show(const void *data)
{
	const int *d = data;
	printf("%d\n", *d);
}

int main(void)
{
	int arr[10] = {5, 1, 8, 5, 7, 6, 2, 9, 3, 4};
	tree_t *tree;

	treeInit(sizeof(int), &tree);
	
	for (int i = 0; i < 10; i++) {
		treeInsert(tree, arr+i, cmpInt);
	}

	treeMid(tree, show);

	return 0;
}

