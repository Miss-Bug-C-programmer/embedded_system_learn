#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void handler2(int s)
{
	write(1, "$", 1);
}

static void handler1(int s)
{
	for (int i = 0; i < 3; i++) {
		write(1, "!", 1);
		sleep(1);
	}
}

int main(void)
{
	signal(2/*SIGINT*/, handler1);
	signal(SIGQUIT, handler2);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

