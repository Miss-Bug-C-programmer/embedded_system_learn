#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void)
{
	void *ptr;
	pid_t pid;
	
	// 共享内存
	ptr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, \
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	pid = fork();
	// if error;

	if (pid == 0) {
		memcpy(ptr, "hello everyony", 14);
		exit(0);
	}
	wait(NULL);

	puts(ptr);
	munmap(ptr, 1024);

	exit(0);
}

