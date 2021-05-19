/*
 统计argv[1]文件所占磁盘空间大小
 argv[1]--->目录文件-->读目录
 		--->非目录文件
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <glob.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#define BUFSIZE	128

long mydu(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)	
		return 1;
	printf("%ldk\n", mydu(argv[1]));

	return 0;
}

long mydu(const char *path)
{
	struct stat res;
	long ret = 0;
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	char buf[BUFSIZE] = {};

	if (stat(path, &res) != 0) {
		perror("stat()");
		return -1;
	}
	if (!S_ISDIR(res.st_mode))
		ret = res.st_blocks / 2;
	else {
		ret = res.st_blocks / 2; // 目录本身	
		dp = opendir(path);
		if (NULL == dp) {
			perror("opendir()");
			goto ERROR;
		}
		while (1) {
			entry = readdir(dp);
			if (NULL == entry) {
				if (errno) {
					perror("readdir()");
					goto ERROR;
				}
				break;
			}
			if (!strcmp(entry->d_name, ".") || \
					!strcmp(entry->d_name, ".."))
				continue;
			memset(buf, '\0', BUFSIZE);
			strncpy(buf, path, BUFSIZE);
			strcat(buf, "/");
			strcat(buf, entry->d_name);
			ret += mydu(buf);
		}
		closedir(dp);
	}

	return ret;
ERROR:
	return -1;
}



