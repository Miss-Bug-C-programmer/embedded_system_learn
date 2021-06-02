#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define START 	100
#define END		300
#define THR_NR	(END)-(START)+1

static int isPrimer(int n)
{
	int i;

	for (i = 2; i < n; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}

static void *thrJob(void *arg)
{
	sleep(1);

	int n;

	n = (int)arg;

	if (isPrimer(n)) {
		printf("%d is a primer\n", n);
	}
	
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tids[THR_NR] = {};
	int i;
	int err;
	
	for (i = START; i <= END; i++) {
		err = pthread_create(tids+i-START, NULL, thrJob, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (i = 0; i < THR_NR; i++)
		pthread_join(tids[i], NULL);

	exit(0);
}

