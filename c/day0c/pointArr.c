#include <stdio.h>

int main(int argc, char **argv)
{
	// 指针数组
	char *arr[3] = {"chengchao", "zhengdaguang", "hezetian"};

	for (int i = 0; i < 3; i++) {
		puts(arr[i]);
	}

	for (int i = 0; i < argc; i++) {
		puts(argv[i]);
	}

	return 0;
}


