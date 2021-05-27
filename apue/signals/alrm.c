#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static void alrm_handler(int s)
{
//	alarm(3);
	write(1, "!", 1);
}

int main(void)
{
	struct itimerval itv;

	signal(SIGALRM, alrm_handler);
//	alarm(3);

	itv.it_interval.tv_sec = 3;
	itv.it_interval.tv_usec = 500000;
	itv.it_value.tv_sec = 0;
	itv.it_value.tv_usec = 100000;

	setitimer(ITIMER_REAL, &itv, NULL);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

