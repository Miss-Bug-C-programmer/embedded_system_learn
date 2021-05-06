#include <stdio.h>
#include <string.h>

#include <llist.h>

static void showStr(const void *data)
{
	char *const*d = data;
	
	printf("%s\n", *d);
}

static int cmpStr(const void *data, const void *key)
{
	char *const*d = data;
	char *const*k = key;

	return strcmp(*d, *k);
}

int main(int argc, char *argv[])
{
	llisthead_t *head = NULL;
	int i;
	char *del;

	llistheadInit(sizeof(char *), &head);

	for (i = 0; i < argc; i++) {
		llistInsert(head, argv+i, LLISTINSERTTAIL);
	}

	del = "afternoon";
	llistDelete(head, &del, cmpStr);
	llistTraval(head, showStr);

	llistDestroy(head);

	return 0;
}

