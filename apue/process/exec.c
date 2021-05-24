#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	char *args[] = {"ls", "-l", NULL};

	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		// execl("/bin/ls", "ls", "-l", NULL);
		// execlp("ls", "ls", "-l", NULL);
		execv("/bin/ls", args);
		perror("execl()");	
		exit(1);
	}

	wait(NULL);

	exit(0);
}

