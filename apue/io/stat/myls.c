#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#define TMBUF	100

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	struct stat res;

	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}
	switch (res.st_mode & S_IFMT) {
		case S_IFSOCK:
			putchar('s');
			break;
		case S_IFREG:
			putchar('-');
			break;
		case S_IFDIR:
			putchar('d');
			break;
		default:
			break;
	
	}

	// 文件的权限
	if (res.st_mode & S_IRUSR)
		putchar('r');
	else
		putchar('-');
	if (res.st_mode & S_IWUSR)
		putchar('w');
	else
		putchar('-');
	if (res.st_mode & S_IXUSR) {
		if (res.st_mode &  S_ISUID)
			putchar('s');
		else
			putchar('x');
	} else
		putchar('-');
	// 特殊权限u+s g+s o+t

	// 文件硬链接个数
	printf(" %ld ", res.st_nlink);

	// 文件拥有者名 man 5 passwd man 3 getpwuid()
	struct passwd *p; 
	p = getpwuid(res.st_uid);
	printf("%s ", p->pw_name);

	// 所属组名 man 5 group man 3 getgrgid
	struct group *g;
	g = getgrgid(res.st_gid);
	printf("%s ", g->gr_name);

	// 文件字节大小 != 所占磁盘空间大小
	printf("%ld ", res.st_size);

	// 文件mtime
	struct tm *tmp;
	char tmbuf[TMBUF] = {};

	tmp = localtime(&res.st_mtime);
	strftime(tmbuf, TMBUF, "%m月 %d %H:%M", tmp);
	printf("%s ", tmbuf);

	printf("%s", argv[1]);

	putchar('\n');

	return 0;
}

