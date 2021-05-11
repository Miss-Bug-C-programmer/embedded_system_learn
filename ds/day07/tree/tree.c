#include <stdlib.h>
#include <string.h>

#include "tree.h"

int treeInit(int size, tree_t **t)
{
	*t = malloc(sizeof(tree_t));
	if (NULL == *t)
		return -1;
	(*t)->root = NULL;
	(*t)->size = size;

	return 0;
}

static int __insert(struct node_st **r, const void *data, cmp_t cmp, int size)
{
	if (*r == NULL) {
		struct node_st *new;

		new = malloc(sizeof(struct node_st)+size);
		if (NULL == new)
			return -1;
		memcpy(new->data, data, size);
		*r = new;
		return 0;
	}
	
	// 树不为空
	if (cmp(data, (*r)->data) > 0)
		return __insert(&(*r)->right, data, cmp, size);
	else
		return __insert(&(*r)->left, data, cmp, size);
}

int treeInsert(tree_t *rt, const void *data, cmp_t cmp)
{
	__insert(&rt->root, data, cmp, rt->size);
}

static void __travalMid(const struct node_st *root, pri_t pri)
{
	if (root == NULL)
		return;
	__travalMid(root->left, pri);
	pri(root->data);
	__travalMid(root->right, pri);
}

int treeMid(const tree_t *rt, pri_t pri)
{
	__travalMid(rt->root, pri);
	return 0;
}

