#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>
#include <queue.h>

char *midToPre(const char *mid);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	char *p = midToPre(argv[1]);
	if (NULL == p) {
		printf("invalid expression\n");
	} else {
		puts(p);
		free(p);
	}

	return 0;
}

// 判断是否为操作数
static int isNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

// 判断是否是四则运算符
static int isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 运算符优先级
static int operatorValue(char ch)
{
	int val = 0;

	if (ch == '+' || ch  == '-')
		val = 1;
	else if (ch == '*' || ch == '/')
		val = 2;
	return val;
}

char *midToPre(const char *mid)
{
	stack_t *s;	
	queue_t *q;
	int len;
	char top;
	char *ret = NULL;
	int i;

	len = strlen(mid);

	stackInit(sizeof(char), len, &s);
	queueInit(sizeof(char), len, &q);

	while (*mid) {
		if (isNumber(*mid))
			enq(q, mid);
		else if (*mid == '(') 
			push(s, mid);
		else if (isOperator(*mid)) {
			while (!stackIsEmpty(s)) {
				pop(s, &top);
				if (operatorValue(top) >= operatorValue(*mid))
					enq(q, &top);
				else {
					push(s, &top);
					break;
				}
			}
			push(s, mid);
		} else if (*mid == ')') {
			while (!stackIsEmpty(s)) {
				pop(s, &top);
				if (top == '(')
					break;
				enq(q, &top);
			}
			if (stackIsEmpty(s) && top != '(')
				goto ERROR;
		} else
			goto ERROR;
		mid++;
	}
	while (!stackIsEmpty(s)) {
		pop(s, &top);
		enq(q, &top);
	}

	ret = malloc(len+1);
	i = 0;
	while (!queueIsEmpty(q)) {
		deq(q, &top);	
		ret[i] = top;
		i++;
	}
	ret[i] = '\0';	
	if (i < len) {
		ret = realloc(ret, i+1);
		// if error
	}
	stackDestroy(s);
	queueDestroy(q);

	return ret;
ERROR:
	stackDestroy(s);
	queueDestroy(q);
	return NULL;
}

