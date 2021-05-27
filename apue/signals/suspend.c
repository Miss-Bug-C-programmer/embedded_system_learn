#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void handler(int s)
{
	write(1, "!", 1);
}

int main(void)
{
	int i, j;
	sigset_t set, oldset;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);

	// 初始化信号集
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	sigprocmask(SIG_BLOCK, &set, &oldset);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
		sigsuspend(&oldset);
	}


	exit(0);
}

