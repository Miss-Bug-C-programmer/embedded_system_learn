#include <stdio.h>
#include <stdlib.h>

#include "medialib.h"

int main(void)
{
	mlibChnList_t *mlib;
	int chnnr;

	mlibGetChnList(&mlib, &chnnr);

	for (int i = 0; i < chnnr; i++) {
		printf("%d %s\n", mlib[i].chnid, mlib[i].descr);
	}

	exit(0);
}
