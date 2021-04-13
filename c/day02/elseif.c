/*
 score
 90~100:A
 80~89:B
 70~79:C
 60:69:D
 0~59:不合格
 */

#include <stdio.h>

int main(void)
{
	int score;

	printf("请输入你的成绩:");
	scanf("%d", &score);

	if (score >= 90 && score <= 100)
		printf("A\n");
	else if (score >= 80 && score < 90)
		printf("B\n");
	else if (score >= 70 && score <= 79)
		printf("C\n");
	else if (score >= 60 && score <= 69)
		printf("D\n");
	else if (score >= 0 && score < 60)
		printf("不合格\n");
	else 
		printf("无效输入\n");
	
	return 0;
}




