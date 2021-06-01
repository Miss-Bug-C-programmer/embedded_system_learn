#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	char *ptr;
	struct stat res;

	if (argc < 2)
		exit(1);

	fd = open(argv[1], O_RDONLY);
	// if error

	fstat(fd, &res);

	ptr = mmap(NULL, res.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	puts(ptr);

	munmap(ptr, res.st_size);
	close(fd);

	exit(0);
}

