#include <stdio.h>
#include <string.h>

#include "seq.h"

static void showChar(const void *data)
{
	const char *c = data;

	putchar(*c);
}

int main(int argc, char *argv[])
{
	seqlist_t *myseqlist;
	int i;

	if (argc < 2)
		return 1;
	
	seqlistInit(sizeof(char), strlen(argv[1]), &myseqlist);

	for (i = 0; argv[1][i]; i++) {
		seqlistAdd(myseqlist, argv[1]+i);
	}

	seqlistTraval(myseqlist, showChar);

	seqlistDestroy(myseqlist);

	return 0;
}






