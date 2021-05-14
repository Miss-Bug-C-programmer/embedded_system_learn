#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 10

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	int fd;
	char buf[BUFSIZE] = {};
	int cnt;

	fd = open(argv[1], O_RDONLY);
	if (-1 == fd) {
		perror("open()");
		return 1;
	}

	printf("cur seek:%ld\n", lseek(fd, -10, SEEK_END));

	cnt = read(fd, buf, BUFSIZE);
	write(1, buf, cnt);

	close(fd);

	return 0;
}

