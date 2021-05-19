#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	/*
	 ./a.out -l -aargument -h /etc/passwd
	 选项:-l -a -h
	 非选项参数:/etc/passwd
	 选项的参数:argument
	 */
	int ch;

	while (1) {
		ch = getopt(argc, argv, "-a:hl");
		if (-1 == ch)
			break;
		switch (ch) {
			case 'l':
				printf("-l...\n");
				break;
			case 'a':
				printf("required argument -a\n");
				puts(optarg);
				break;
			case 'h':
				printf("-h...\n");
				break;
			case '?':
				printf("i don't know\n");
				break;
			case 1:
				printf("nonoption argv-element:%s\n", argv[optind-1]);
				break;
		}
	}

	return 0;
}

