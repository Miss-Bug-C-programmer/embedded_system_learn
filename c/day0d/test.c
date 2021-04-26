#include <stdio.h>
/*
定义一个学生结构体(姓名，成绩), 现有10个学生，读入学生信息，并将成绩几个的学生名单列出
 */

#define NAMESIZE	32
#define N			10

typedef struct stu_st {
	char name[NAMESIZE];
	int score;
}stu_t;

int main(void)
{
	stu_t stu[N];
	// stu_t *p = calloc(N, sizeof(stu_t));
	int i;	

	for (i = 0; i < N; i++) {
		scanf("%s%d", stu[i].name, &stu[i].score);
	}

	printf("以下同学及格:");
	for (i = 0; i < N; i++) {
		if (stu[i].score >= 60)
			printf("%s\n", stu[i].name);
	}

	return 0;
}


