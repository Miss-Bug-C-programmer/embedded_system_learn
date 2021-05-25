#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		exit(1);

	if (write(atoi(argv[1]), "good morning", 12) == -1) {
		perror("write()");
		exit(1);
	}

	return 0;
}

