#include <stdio.h>
#include <stack.h>
#include <queue.h>

static int seqBall(queue_t *q)
{
	queue_t *tmpq = NULL;
	int pre, cur;
	int ret = 1;

	queueInit(sizeof(int), 27, &tmpq);
	
	// 132456789.....
	deq(q, &pre);
	printf("%d ", pre);
	enq(tmpq, &pre);
	while (!queueIsEmpty(q)) {
		deq(q, &cur);
		printf("%d ", cur);
		enq(tmpq, &cur);
		if (cur < pre) {
			ret = 0;
		}
		pre = cur;
	}
	printf("\n");

	while (!queueIsEmpty(tmpq)) {
		deq(tmpq, &cur);
		enq(q, &cur);
	}
	queueDestroy(tmpq);

	return ret;
}

int main(void)
{
	queue_t *ball;
	stack_t *oneMin, *fiveMin, *oneHour;
	int n, tmp;
	int days = 0;

	queueInit(sizeof(int), 27, &ball);
	stackInit(sizeof(int), 4, &oneMin);
	stackInit(sizeof(int), 11, &fiveMin);
	stackInit(sizeof(int), 11, &oneHour);

	// 27球入队
	for (int i = 1; i < 28; i++) {
		enq(ball, &i);
	}

	while (1) {
		deq(ball, &n);
		if (!stackIsFull(oneMin))
			push(oneMin, &n);
		else {
			while (!stackIsEmpty(oneMin)) {
				pop(oneMin, &tmp);
				enq(ball, &tmp);
			}
			if (!stackIsFull(fiveMin))
				push(fiveMin, &n);
			else {
				while (!stackIsEmpty(fiveMin)) {
					pop(fiveMin, &tmp);
					enq(ball, &tmp);
				}
				if (!stackIsFull(oneHour))
					push(oneHour, &n);
				else {
					while (!stackIsEmpty(oneHour)) {
						pop(oneHour, &tmp);
						enq(ball, &tmp);
					}
					enq(ball, &n);
					days ++;
					printf("days:%d\n", days);
					// 所有的球回到队列
					if (seqBall(ball))
						break;

				}
			}
		}
	}

	printf("days:%d\n", days);

	queueDestroy(ball);
	stackDestroy(oneMin);
	stackDestroy(fiveMin);
	stackDestroy(oneHour);

	return 0;
}

