// 创建"/tmp/out"文件并将0写入，再创建20进程，20进程同时读"/tmp/out"文件的数据，将读到的数值+1再写回去。问最终文件中的值为多少
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define FLNAME	"/tmp/out"
#define PRO_NR	20
#define BUFSIZE	10

static int semid;

//取信号 
static void P()
{
	struct sembuf op;

	op.sem_num = 0; // 下标0
	op.sem_op = -1; // 取一个信号
	op.sem_flg = 0;

	if (semop(semid, &op, 1) == -1) {
		perror("semop()");
		abort();
	}
}

// 还
static void V()
{
	struct sembuf op;

	op.sem_num = 0; // 下标0
	op.sem_op = 1; // 取一个信号
	op.sem_flg = 0;

	if (semop(semid, &op, 1) == -1) {
		perror("semop()");
		abort();
	}
}

static void rwFile(int fd)
{
	char buf[BUFSIZE] = {};

	// 竞争--->同步
	
	P();
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, BUFSIZE);
	snprintf(buf, BUFSIZE, "%d", atoi(buf)+1);
	sleep(1);
	lseek(fd, 0, SEEK_SET);
	write(fd, buf, strlen(buf));
	V();
	close(fd);
}

int main(void)
{
	int fd;
	pid_t pid;
	int i;

	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == semid) {
		perror("semid()");
		exit(1);
	}
	// 初始化信号, 向集合中下标为0的信号量初始化1个信号
	semctl(semid, 0, SETVAL, 1);

	fd = open(FLNAME, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (-1 == fd) {
		perror("open()");
		exit(1);
	}
	write(fd, "0", 1);
	// close(fd);

	for (i = 0; i < PRO_NR; i++) {
		pid = fork();
		// if error;
		if (0 == pid) {
			rwFile(fd);		
			exit(0);
		}
	}

	for (i = 0; i < PRO_NR; i++)
		wait(NULL);

	close(fd);

	exit(0);
}

