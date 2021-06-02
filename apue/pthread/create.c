#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// 线程函数
static void *thrs(void *s)
{
	for (int i = 0; i < 3; i++) {
		write(1, "!", 1);
		sleep(1);
	}

	return NULL;
}

int main(void)
{
	pthread_t tid;
	int err;

	if ((err = pthread_create(&tid, NULL, thrs, NULL)) != 0) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));	
		exit(1);
	}

	for (int i = 0; i < 3 ; i++) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}

