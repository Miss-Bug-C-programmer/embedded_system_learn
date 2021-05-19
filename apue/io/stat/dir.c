#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
/*
	计算argv[1]目录字节总大小
 */

#define BUFSIZE	128	

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	DIR *dp;
	struct dirent *entry;
	char path[BUFSIZE] = {};
	struct stat res;
	int size = 0;

	stat(argv[1], &res);
	if (!S_ISDIR(res.st_mode))
		return 1;

	dp = opendir(argv[1]);
	if (NULL == dp) {
		perror("opendir()");
		return 1;
	}

	while (1) {
		entry = readdir(dp);
		if (NULL == entry) {
			if (errno)
				goto ERROR;
			break;
		}
		// printf("%s\n", entry->d_name);
		memset(path, '\0', BUFSIZE);
		strcpy(path, argv[1]);
		strcat(path, "/");
		strcat(path, entry->d_name);
		stat(path, &res);
		size += res.st_size;
	}

	printf("size:%d\n", size);

	closedir(dp);

	return 0;
ERROR:
	closedir(dp);
	return 1;
}

