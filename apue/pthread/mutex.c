#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define START 	100
#define END 	300
#define THRNR	4
/*
 > 0 所分配的任务值
 == 0 任务值被线程取走
 == -1 所有任务发放完成
 */
static int job; // 临界区
// 初始化互斥量---->使临界区同步
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static int isPrimer(int n)
{
	int i;

	for (i = 2; i < n; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}

// 任务线程
static void *thrJob(void *s) 
{
	int num;

	while (1) {
		pthread_mutex_lock(&mut);	
		if (job == -1) {
			pthread_mutex_unlock(&mut);
			break;
		}
		if (job == 0) {
			pthread_mutex_unlock(&mut);
			sched_yield(); // 出让调度器
			continue;
		}
		num = job;
		job = 0;
		pthread_mutex_unlock(&mut);

		if (isPrimer(num))
			printf("%d is a primer\n", num);
	}

	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tids[THRNR] = {};
	int i;
	
	for (i = 0; i < THRNR; i++) {
		pthread_create(tids+i, NULL, thrJob, NULL);
		// if error
	}

	// 发放任务
	for (i = START; i <= END; i++) {
		pthread_mutex_lock(&mut);	
		while (job != 0) {
			// 上一次任务未完成
			pthread_mutex_unlock(&mut);
			sched_yield();	
			pthread_mutex_lock(&mut);
		}
		job = i;
		pthread_mutex_unlock(&mut);
	}

	pthread_mutex_lock(&mut);
	while (job != 0) {
		// 最后一个任务还未完成
		pthread_mutex_unlock(&mut);
		sched_yield();	
		pthread_mutex_lock(&mut);
	}
	job = -1;
	pthread_mutex_unlock(&mut);

	for (i = 0; i < THRNR; i++)
		pthread_join(tids[i], NULL);

	pthread_mutex_destroy(&mut);

	exit(0);
}





