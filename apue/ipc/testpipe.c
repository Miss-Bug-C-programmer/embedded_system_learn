#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE	100

static int cpFile(int rfd, int wfd)
{
	char buf[BUFSIZE] = {};
	int cnt;

	while (1) {
		cnt = read(rfd, buf, BUFSIZE);	
		if (cnt == -1) {
			if (errno == EINTR)
				continue; // 假错
			perror("read()");
			return -1;
		}
		if (cnt == 0)
			break;
		write(wfd, buf, cnt);	
	}	
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		exit(1);
	int pfd[2];
	int fd;
	pid_t pid;

	do {
		fd = open(argv[1], O_RDONLY);
		if (-1 == fd) {
			if (errno == EINTR)
				continue;
			perror("open()");
			exit(1);
		}
		break;
	} while (1);

	if (pipe(pfd) == -1) {
		perror("pipe()");
		goto ERROR;
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR2;
	}
	if (pid == 0) {
		fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		// if error
		close(pfd[1]);
		cpFile(pfd[0], fd);
		close(pfd[0]);
		close(fd);
		exit(0);
	}
	close(pfd[0]);
	cpFile(fd, pfd[1]);
	close(pfd[1]);
	close(fd);

	wait(NULL);
	
	exit(0);
ERROR2:
	close(pfd[0]);
	close(pfd[1]);
ERROR:
	close(fd);
	exit(1);
}

