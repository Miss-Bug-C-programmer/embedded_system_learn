#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#define FLNAME	"/tmp/out"
#define BUFSIZE	100

int mydaemon(void);
int main(void)
{
	time_t tm;
	struct tm *tmp = NULL;
	char buf[BUFSIZE] = {};
	FILE *fp;

	// 创建链接
	openlog("mydaemon", LOG_PID | LOG_PERROR, LOG_DAEMON);

	if (mydaemon() == -1) {
		// fprintf(stderr, "mydaemon() failed\n");
		syslog(LOG_ERR, "mydaemon() failed");
		exit(1);
	}

	fp = fopen(FLNAME, "w");
	if (NULL == fp) {
		// perror("fopen()");
		syslog(LOG_ERR, "fopen():%s", strerror(errno));
		exit(1);
	}

	while (1) {
		time(&tm);	
		tmp = localtime(&tm);
		strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", tmp);
		fputs(buf, fp);
		fflush(fp);

		syslog(LOG_DEBUG, "%s done", buf);

		sleep(1);
	}

	fclose(fp);
	exit(0);
}

int mydaemon(void)
{
	pid_t pid;
	int fd;

	pid = fork();
	if (-1 == pid) {
		perror("fork()");
		return -1;
	}
	if (pid > 0)
		exit(0);
	if (setsid() == -1) {
		perror("setsid()");
		return -1;
	}
	// PID == PGID == SID no tty

	umask(0);
	chdir("/");

	fd = open("/dev/null", O_RDWR);
	if (-1 == fd) {
		perror("open()");
		return -1;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);

	return 0;
}








