#ifndef __TREE_H
#define __TREE_H

// 变长结构体
struct node_st {
	struct node_st *left;
	struct node_st *right;
	char data[0];
};

typedef struct {
	struct node_st *root;
	int size;
}tree_t;

typedef int (*cmp_t)(const void *data, const void *node);
typedef void (*pri_t)(const void *data);

int treeInit(int size, tree_t **t);
int treeInsert(tree_t *rt, const void *data, cmp_t cmp);
int treeMid(const tree_t *rt, pri_t pri);

#endif

