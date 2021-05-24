#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	if (argc < 2)
		exit(1);

	pid_t pid;
	int fd;
	char buf[BUFSIZE] = {};
	
	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (-1 == fd) {
		perror("open()");
		exit(1);
	}

	printf("hello world");
	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		exit(1);
	}

	if (0 == pid) {
		// child
		printf("child pid:%d\n", getpid());

		sleep(3);
		write(fd, "good afternoon", 14);
		
		close(fd);
		exit(EXIT_SUCCESS); // EXIT_FAILURE
	}
//	sleep(1);
	wait(NULL);
	printf("%ld\n", lseek(fd, 0, SEEK_CUR));
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, BUFSIZE);
	puts(buf);
	close(fd);

	printf("parent pid:%d\n", getpid());

	exit(0);
}

