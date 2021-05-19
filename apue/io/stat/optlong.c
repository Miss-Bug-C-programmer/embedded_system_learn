#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	struct option opts[4] = {
		{"help", no_argument, NULL, 'e'},
		{"test", required_argument, NULL, 't'},
		{"long", optional_argument, NULL, 'o'},
		{0, 0, 0, 0}
	};
	int c;

	while (1) {
		c = getopt_long(argc, argv, "lm", opts, NULL);
		if (-1 == c)
			break;
		switch(c) {
			case 'l':
				printf("option -l\n");
				break;
			case 'm':
				printf("option -m \n");
				break;
			case 'e':
				printf("long option help\n");
				break;
			case 't':
				printf("long option test\n");
				printf("argument:%s\n", optarg);
				break;
			case 'o':
				printf("long option long\n");
				if (optarg != NULL)
					puts(optarg);
				break;
			case '?':
				printf("i don't know\n");
				break;
		}
	}

	return 0;
}

