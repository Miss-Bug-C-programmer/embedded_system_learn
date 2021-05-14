#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	//if error

#if 0
	close(1);
	dup(fd);
#endif
	dup(fd, 1);
	write(1, "hello world", 11);

	close(fd);

	return 0;
}

