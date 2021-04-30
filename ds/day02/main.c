#include <stdio.h>

#include "list.h"

#define NAMESIZE	32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

static void showStu(const void *data)
{
	const struct stu_st *s = data;
	printf("%d %s\n", s->id, s->name);
}

int main(void)
{
	listhead_t *head;
	struct stu_st stu;
	int ids[] = {3,1,6,8,9,7,2,5};
	int i;
	
	listheadInit(sizeof(struct stu_st), &head);

	for (i = 0; i < sizeof(ids) / sizeof(int); i++) {
		stu.id = ids[i];
		snprintf(stu.name, NAMESIZE, "stu%d", ids[i]);
		listInsert(head, &stu, TAILINSERT);
	}

	listTraval(head, showStu);

	listDestroy(head);

	return 0;
}
