#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd;
	int num = 100;

	printf("hello world");
	pid = vfork();
	if (-1 == pid) {
		perror("fork()");
		exit(1);
	}

	if (0 == pid) {
		// child
		num ++;
		printf("child pid:%d\n", getpid());
		sleep(3);
		_exit(EXIT_SUCCESS); // EXIT_FAILURE
	}

	printf("num:%d\n", num);
	printf("parent pid:%d\n", getpid());

	exit(0);
}

