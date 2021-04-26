#include <stdio.h>
#include <string.h>

// 结构体
struct stu_st {
	char name[32];
	int age;
	char sex;
	char *tel;
};

int main(void)
{
	// struct stu 结构体类型
	struct stu_st stu1;
	struct stu_st *p;

	p = &stu1;
	
	strcpy(stu1.name, "凯歌");
	stu1.age = 18;
	stu1.sex = 'f';
	stu1.tel = "123456789";

	printf("%s %d %c %s\n", p->name, p->age, p->sex, p->tel);

	return 0;
}

