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
#include <sys/file.h>

#define FLNAME		"/tmp/out"
#define BUFSIZE		100
#define LOCKFILE	"/var/run/mydaemon.pid"

int mydaemon(void);
int already_running(void);
int main(void)
{
	time_t tm;
	struct tm *tmp = NULL;
	char buf[BUFSIZE] = {};
	FILE *fp;

	// 创建链接
	openlog("mydaemon", LOG_PID | LOG_PERROR, LOG_DAEMON);

	if (already_running() == -1) {
		syslog(LOG_ERR, "already_running() failed");
		exit(1);
	}

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

//		syslog(LOG_DEBUG, "%s done", buf);

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

// 单实例
int already_running(void)
{
	int fd;
	char buf[BUFSIZE] = {};

	fd = open(LOCKFILE, O_RDWR | O_CREAT, 0666);
	if (fd ==-1) {
		syslog(LOG_ERR, "open():%s", strerror(errno));
		return -1;
	}

	if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
		syslog(LOG_ERR, "flock():%s", strerror(errno));	
		close(fd);
		return -1;
	}

	ftruncate(fd, 0);
	snprintf(buf, BUFSIZE, "%d", getpid());
	write(fd, buf, strlen(buf));
	return 0;
}





