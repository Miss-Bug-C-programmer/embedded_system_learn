#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE	100

// 子进程将argv[1]全部读出来，传输给父进程，父进程接收到后写到argv[2]文件中

int main(void)
{
	int pfd[2];
	pid_t pid;
	char buf[BUFSIZE] = {};

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}

	pid = fork();	
	if (-1 == pid) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		close(pfd[0]);
		write(pfd[1], "good afternoon", 14);
		close(pfd[1]);
		exit(0);
	}
	close(pfd[1]);
	read(pfd[0], buf, BUFSIZE);
	close(pfd[0]);
	puts(buf);

	wait(NULL);

	exit(0);
}

