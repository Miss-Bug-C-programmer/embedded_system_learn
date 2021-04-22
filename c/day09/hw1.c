#include <stdio.h>

#define N	10

int main(void)
{
	char arr[N] = {};
	int i;
	int letterCnt = 0;
	int spaceCnt = 0;
	int digitalCnt = 0;
	int otherCnt = 0;

	for (i = 0; i < N-1; i++) {
		scanf("%c", arr+i);	
		if (arr[i] == '\n') {
			arr[i] = '\0';
			break;
		}
	}

	for (i = 0; arr[i]; i++) {
		if (arr[i] >= 'A' && arr[i] <= 'Z' || \
				arr[i] >= 'a' && arr[i] <= 'z')
			letterCnt ++;
		else if (arr[i] >= '0' && arr[i] <= '9')
			digitalCnt++;
		else if (arr[i] == ' ')
			spaceCnt ++;
		else
			otherCnt ++;
	}

	printf("字母个数:%d\n", letterCnt);
	printf("数字个数:%d\n", digitalCnt);
	printf("空格个数:%d\n", spaceCnt);
	printf("其他个数:%d\n", otherCnt);

	return 0;
}

