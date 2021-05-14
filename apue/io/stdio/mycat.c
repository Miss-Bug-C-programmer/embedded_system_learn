#include <stdio.h>

#define BUFSIZE	10

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	FILE *fp;
	int ch;
	int cnt;
	char buf[BUFSIZE] = {};

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		perror("fopen()");
		return 1;
	}

	while (1) {
#if 0
		// 按字节读写
		ch = fgetc(fp);
		if (EOF == ch) {
			if (ferror(fp))
				goto ERROR;
			break;
		}
		fputc(ch, stdout);
#endif
#if 0
		// 按行
		if (fgets(buf, BUFSIZE, fp) == NULL) {
			if (ferror(fp))
				goto ERROR;
			break;
		}
		fputs(buf, stdout);
#endif
		// 结构化读写
		cnt = fread(buf, 1, BUFSIZE, fp); 
		if (0 == cnt) {
			if (feof(fp))
				break;
			fprintf(stderr, "fread() failed\n");
			goto ERROR;
		}
		fwrite(buf, 1, cnt, stdout);
	}

	fclose(fp);

	return 0;
ERROR:
	fclose(fp);
	return 1;
}

