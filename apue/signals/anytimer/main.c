#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void alrm_handler(int s)
{
	write(1, "hello world", 11);
}

int main(void)
{
	signal(SIGALRM, alrm_handler);

	anytimer(5, alrm_handler)
	anytimer(10, alrm_handler)
	anytimer(3, alrm_handler)
	// alarm(5);
	// alarm(10);
	// alarm(3);

	// ***helloworld**helloworld*****helloworld*****
	while (1){
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

