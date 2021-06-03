#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define THRNR	5

static int jobid = -1;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *thrJob(void *arg)
{
	int selfid = (int)arg;

	while (1) {
		pthread_mutex_lock(&mut);	
		while (jobid != selfid) {
			pthread_cond_wait(&cond, &mut);
		}
		fprintf(stdout, "%c", 'a'+selfid);
		fflush(NULL);
		jobid = -1;
		sleep(1);
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}
}

int main(void)
{
	pthread_t tids[THRNR] = {};	
	int i;
	int err;

	alarm(50);

	for (i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, NULL, thrJob, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", \
					strerror(err));
			exit(1);
		}
	}

	for (i = 0; ; i = (i+1) % THRNR) {
		pthread_mutex_lock(&mut);	
		while (jobid != -1) {
			pthread_cond_wait(&cond, &mut);
		}
		jobid = i;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);
	}

	pthread_mutex_destroy(&mut);

	exit(0);
}

