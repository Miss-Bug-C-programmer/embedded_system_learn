#ifndef __SEQ_H
#define __SEQ_H
// 条件编译：防止头文件多次包含的时候多次展开

/*
   类型的定义
   函数的声明
 */
// 抽象数据类型
typedef struct {
	void *arr;// 数据域的首地址
	int size;// 数据每个成员字节大小
	int nmembs; // 已存储的成员个数
	int capacity;// 容量
}seqlist_t;

typedef void (*pri_t)(const void *);

// 接口函数
/*
 初始化顺序表结构
 */
int seqlistInit(int size, int capacity, seqlist_t **sl);

/*
	增加新的元素 
 */
int seqlistAdd(seqlist_t *sl, const void *data);

/*
 	遍历
 */
void seqlistTraval(const seqlist_t *sl, pri_t pri);

/*
 	销毁
 */
void seqlistDestroy(seqlist_t *sl);

#endif


