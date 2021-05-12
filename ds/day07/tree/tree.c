#include <stdlib.h>
#include <stdio.h>
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

static struct node_st *maxNode(struct node_st *root)
{
	if (NULL == root)
		return NULL;
	if (NULL == root->right)
		return root;
	return maxNode(root->right);
}

static int __delete(struct node_st **root, const void *key, cmp_t cmp)
{
	if (*root == NULL) {
		return -1;
	}
	if (cmp(key, (*root)->data) == 0) {
		struct node_st *del, *l, *r;
		del = *root;
		l = del->left;
		r = del->right;
		if (NULL == l)	{
			*root = r;
		} else {
			*root = l;
			if (NULL != r)
				maxNode(l)->right = r;
			del->left = del->right = NULL;
			free(del);
		}
		return 0;
	}
	if (cmp(key, (*root)->data) > 0)
		return __delete(&(*root)->right, key, cmp);
	else
		return __delete(&(*root)->left, key, cmp);
}

int treeDelete(tree_t *rt, const void *key, cmp_t cmp)
{
	return __delete(&rt->root, key, cmp);
}

static void __destroy(struct node_st **root)
{
	if (NULL == *root)
		return;
	__destroy(&(*root)->left);
	__destroy(&(*root)->right);
	free(*root);
	*root = NULL;
}

void treeDestroy(tree_t *rt)
{
	__destroy(&rt->root);	
}

static void __show(const struct node_st *root, int level, pri_t pri)
{
	if (root == NULL)
		return;
	__show(root->right, level+1, pri);
	for (int i = 0; i < level; i++)
		printf("    ");
	pri(root->data);
	__show(root->left, level+1, pri);
}

void treeShow(const tree_t *rt, pri_t pri)
{
	__show(rt->root, 0, pri);
}
