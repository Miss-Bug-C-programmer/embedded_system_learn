#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

static void *thrJob(void *s)
{
	int i;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

	for (i = 0; i < 20; i++) {
		if (i == 10)
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		write(1, "*", 1);
		sleep(1);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid;
	int i;

	pthread_create(&tid, NULL, thrJob, NULL);
	// if error

	for (i = 0; i < 5; i++)	{
		write(1, "!", 1);
		sleep(1);
	}
	pthread_cancel(tid);

	pthread_join(tid, NULL);

	exit(0);
}

