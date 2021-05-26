#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void handler1(int s)
{

}

int main(void)
{
	pid_t pid;

	signal(SIGINT, handler1);
	pid = fork();
	// if error

	if (pid == 0) {
		pause();
		printf("caught the signal\n");
		exit(0);
	}
	sleep(1);
	kill(pid, SIGINT);
	wait(NULL);

	exit(0);
}

