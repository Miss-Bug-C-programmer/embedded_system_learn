#include <stdio.h>
#include <string.h>
#include <shadow.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 3)	
		return 1;

	char *cry;
	struct spwd *p = getspnam(argv[1]);
	if (NULL == p) {
		perror("getspnam()");	
		return 1;
	}
	cry = crypt(argv[2], p->sp_pwdp);
	if (strcmp(p->sp_pwdp, cry) == 0) {
		printf("登录成功\n");
	} else {
		printf("鉴定错误\n");
	}

	return 0;
}

