#ifndef __LQUEUE_H
#define __LQUEUE_H
/*
 队列:特殊的线性结构,允许在表的一端插入，另一端删除结构，
 插入动作称为入队(队尾)，删除称为出队(队头)
 存储方式:
 	顺序
	链式
 基本操作:
 	队列初始化
	入队
	出队
	队列是否为空
	销毁
 */
#include <llist.h>

typedef llisthead_t lqueue_t;

int lqueueInit(int size, lqueue_t **lq);
int lqueueEnq(lqueue_t *lq, const void *data);
int lqueueDeq(lqueue_t *lq, void *data);
int lqueueEmpty(const lqueue_t *lq);
void lqueueDestroy(lqueue_t *lq);

#endif



