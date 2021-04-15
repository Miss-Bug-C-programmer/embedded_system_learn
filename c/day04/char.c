#include <stdio.h>

/*
字符类型----》man ascii 

// 将读入的字符大小写转换
 */

int main(void)
{
	char ch;
	char c;

	ch = 'A';
	
	scanf("%c", &c);

	printf("ch:%c, c:%c\n", ch, c);
	printf("ch:%d, c:%d\n", ch, c);

	if (c >= 'A' && c <= 'Z')
		c = c + ('a' - 'A');
	else if (c >= 'a' && c <= 'z')
		c = c - ('a' - 'A');

	printf("转换后c:%c\n", c);

	return 0;
}

