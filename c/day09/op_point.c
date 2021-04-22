#include <stdio.h>

int main(void)
{
	char str[] = "helzo world";
	char *p = NULL; // (void *)0
	p = str;

	// char ch;  ch = *p++;
	printf("%c\n", *p++); // 'h' p-->&str[1]
	printf("%c\n", *(p++)); // 'e' p-->&str[2]
	printf("%c\n", (*p)++); // 'l' 打印完str[2]-->'m'
	printf("%c\n", *++p); // 'z' p--->&str[3] 
	printf("%c\n", ++*p); // '{'

	puts(str); // "hem{o world"

	return 0;
}

