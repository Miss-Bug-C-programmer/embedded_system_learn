#include <stdio.h>
#include <unistd.h>

/*
 标准io缓存区:
 	fopen()--->建立,默认大小4k
	类型:
		无缓存：stderr
		行缓存: stdin stdout
		全缓存: 普通文件
	刷新:
		行缓存遇到'\n',全缓存写满
		进程终止
		fflush()
	作用:
		合并系统调用，减少系统调用的次数，提高效率
 */

int main(void)
{
	write(1, "1", 1);
	printf("a");
	write(1, "2", 1);
	// printf("b");
	fprintf(stderr, "b");
	write(1, "3", 1);
	printf("c");

	// printf("\n");
	fflush(stdout);

	while (1)
		;

	return 0;
}

