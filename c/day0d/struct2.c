#include <stdio.h>

struct color_st {
	int red;
	int blue;
	int green;
};

struct cloth_st {
	float price;
	struct color_st color;
	struct cloth_st *cl;
};

int main(void)
{
	struct cloth_st c;

	c.color.red = 255;
	c.color.blue = 178;

	// 面试题：已知结构体中某个成员的地址，如何求得此结构体首地址
	printf("%d\n", (int)(&((struct cloth_st *)0)->cl));

	return 0;
}

