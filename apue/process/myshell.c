#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>


int parseString(char *s, glob_t *res);
int main(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	glob_t res;
	pid_t pid;

	while (1) {
		printf("[%s]$ ", getenv("PWD"));
		// 等待用户输入的一行命令
		if (getline(&lineptr, &n, stdin) == -1) {
			perror("getline()");
			break;
		}
		// "ls -l" --->strtok(3) --->glob(3)存
		parseString(lineptr, &res);
		// 切割命令 "ls", "-l" --->argv

		if (strcmp((res.gl_pathv)[0], "exit") == 0)
			break;

		pid = fork();
		if (pid == 0) {
			execvp((res.gl_pathv)[0], res.gl_pathv);
			perror("execvp()");
			exit(1);
		}
		wait(NULL);	
	}

	exit(0);
}

int parseString(char *s, glob_t *res)
{
	char *p;
	int i = 0;

	while (1) {
		p = strtok(s, " \n");
		if (NULL == p)
			break;
		glob(p, GLOB_NOCHECK | i * GLOB_APPEND, NULL, res);
		i = 1;
		s = NULL;
	}

	return 0;
}





