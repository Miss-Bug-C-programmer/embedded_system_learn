#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define NAMESIZE 32

struct stu_st {
	int id;
	char name[NAMESIZE];
	struct list_head node;
};

int main(void)
{
	struct stu_st *new;
	int i;
	struct list_head *pos;

	LIST_HEAD(head);

	for (i = 1; i <= 10; i++) {
		new = malloc(sizeof(struct stu_st));
		// if error
		new->id = i;
		snprintf(new->name, NAMESIZE, "stu%d", i);
		list_add(&new->node, &head);
	}

	list_for_each(pos, &head) {
		new = list_entry(pos, struct stu_st, node);
		printf("%d %s\n", new->id, new->name);
	}

	return 0;
}

