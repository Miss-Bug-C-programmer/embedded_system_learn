#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	pid_t pid;

	if (argc < 2)
		exit(1);
	char buf[BUFSIZE] = {};

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (-1 == fd) {
		perror("open()");
		exit(1);
	}

	pid = fork();
	if (-1 == pid) {
		perror("fork()");	
		exit(1);
	}

	if (0 == pid) {
		snprintf(buf, BUFSIZE, "%d", fd);
		fcntl(fd, F_SETFD, 1);
		execl("./access", "./access", buf, NULL);	
		perror("execl()");
		exit(1);
	}

	close(fd);
	wait(NULL);

	exit(0);
}

