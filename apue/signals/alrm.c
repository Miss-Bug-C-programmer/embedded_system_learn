#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void alrm_handler(int s)
{
	alarm(3);
	write(1, "!", 1);
}

int main(void)
{
	signal(SIGALRM, alrm_handler);
	alarm(3);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

