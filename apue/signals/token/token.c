#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#include "token.h"

typedef struct {
	int token;
	int cps;
	int burst;	
}token_t;

static token_t *jobs[MAX];
static int inited = 0;

static void alrmHandler(int s)
{
	int i;

	for (i = 0; i < MAX; i++) {
		if (jobs[i] != NULL) {
			jobs[i]->token += jobs[i]->cps;
			if (jobs[i]->token >= jobs[i]->burst)
				jobs[i]->token = jobs[i]->burst;
		}
	}
}

// 信号工作
static void modulerLoad(void)
{
	struct sigaction act, oldact;
	struct itimerval itv;

	act.sa_handler =  alrmHandler;// 遍历令牌桶库，加令牌
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &oldact);

	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itv, NULL);
}

static int getFreePos(void)
{
	for (int i = 0; i < MAX; i++)
		if (jobs[i] == NULL)
			return i;
	return -1;
}

int tbfInit(int cps, int burst)
{
	token_t *t;
	int pos;

	if (!inited) {
		modulerLoad();
		inited = 1;
	}

	t = malloc(sizeof(token_t));	
	if (NULL == t) {
		perror("malloc()");	
		return -1;
	}
	t->cps = cps;
	t->burst = burst;	
	t->token = 0;

	pos = getFreePos();
	if (pos == -1) {
		free(t);
		return -1;
	}
	jobs[pos] = t;

	return pos;
}

int tbfFetchToken(int tbfId, int fetchTokens)
{
	if (tbfId < 0 || tbfId >= MAX)
		return -1;
	while (jobs[tbfId]->token < fetchTokens)
		pause();
	jobs[tbfId]->token -= fetchTokens;

	return 0;
}

void tbfDestroy(int tbfId)
{
	free(jobs[tbfId]);
	jobs[tbfId] = NULL;
}

void tbfDestroyAll(void)
{
	int i;

	for(i = 0; i < MAX; i++) {
		if (jobs[i] != NULL) {
			free(jobs[i]);
			jobs[i] = NULL;
		}
	}
}



