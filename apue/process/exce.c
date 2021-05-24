/*
 100~300之间有201数值,要求计算有多少个质数并201数值要同时计算
 [pid]xxxis a primer
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define START 	100
#define END		300

static int isPrimer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

int main(void)
{
	pid_t pid;	
	int i;

	for (i = START; i <= END; i++) {
		pid = fork();
		if (-1 == pid) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			if (isPrimer(i))	
				printf("[%d] %d is a primer\n", \
						getpid(), i);
			exit(0);
		}
	}

	for (i = START; i <= END; i++)
		wait(NULL);

	exit(0);
}


