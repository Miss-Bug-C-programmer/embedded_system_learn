#ifndef __LSTACK_H
#define __LSTACK_H

/*
 栈：特殊的线性结构
 只允许在表的一端进行插入删除,将这一端称为栈顶，另一端称为栈底
 基本操作:
 	初始化栈
	入栈
	出栈
	是否空
	销毁
 存储结构:
 	顺序
	链式
 */
#include <llist.h>
typedef llisthead_t lstack_t;

int lstackInit(int size, lstack_t **ls);
int lstackPush(lstack_t *ls, const void *data);
int lstackPop(lstack_t *ls, void *data);
int lstackEmpty(const lstack_t *ls);
void lstackDestroy(lstack_t *ls);

#endif

