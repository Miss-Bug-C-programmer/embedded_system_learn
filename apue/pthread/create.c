#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

// 线程终止处理程序
static void exit_handler1(void *args)
{
	printf("%s is called\n", __FUNCTION__);
}

static void exit_handler2(void *args)
{
	printf("%s is called\n", __FUNCTION__);
}

static void exit_handler3(void *args)
{
	printf("%s is called\n", __FUNCTION__);
}

// 线程函数
static void *thrs(void *s)
{
	pthread_cleanup_push(exit_handler1, NULL);
	pthread_cleanup_push(exit_handler2, NULL);
	pthread_cleanup_push(exit_handler3, NULL);

	for (int i = 0; i < 10; i++) {
		write(1, "!", 1);
		sleep(1);
	}

	pthread_cleanup_pop(1);

	return NULL; // 从启动例程返回
	// pthread_exit(NULL); // (void *)0
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
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

//	exit(0);
	pthread_exit(NULL);
}


