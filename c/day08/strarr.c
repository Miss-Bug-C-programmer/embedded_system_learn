#include <stdio.h>
#include <string.h>

/*
 字符数组和字符串
 "hello"--->'h', 'e', 'l', 'l', 'o', '\0'
 c中没有字符串变量类型--->用字符数组取而代之
 */

int main(void)
{
	char str[5] = {'a', 'b', 'e', 'f', '0'};
	char str2[] = "hello"; // 字符串数组
	char str3[50] = {"hello"};
	char str4[] = {'h', 'e', 'l', 'l', 'o','\0'};
	char str5[] = "good afternoon";
	int i, j;

#if 0
	for (i = 0; str2[i] != '\0'; i++)
		printf("%c", str2[i]);
	printf("\n");
#endif
	puts(str2);
	
	// 字符串长度==不包含'\0'的字节个数
	for (i = 0; str4[i] != '\0'; i++)
		;
	printf("长度:%d\n", i);
	printf("%ld\n", strlen(str4));

	// 字符串复制 str5--->str3
	for (i = 0; str5[i]; i++) {
		str3[i] = str5[i];	
	}
	str3[i] = '\0'; // !!!!!!!!
	puts(str3);
	strcpy(str3, str5);

	// 字符串拼接 str5拼接到str3
	for(i = 0; str3[i]; i++)
		;
#if 0
	for (j = 0; str5[j]; j++) {
		str3[i+j] = str5[j];
	}
	str3[i+j] = '\0';
#endif
	strcpy(str3+i, str5);
	puts(str3);
	// strcat(str3, str5);

	// 字符串比较:从第一个不相等的字符对应的ascii值大的字符串就大
	// "hello" "hi" "helloa"
	// str3 和str5谁大
	for(i = 0; str3[i] || str5[i]; i++) {
		if (str3[i] == str5[i])
			continue;
		if (str3[i] > str5[i]) {
			printf("str3 > str5\n");
		} else {
			printf("str3 < str5\n");
		}
		break;
	}
	if (str3[i] == '\0' && str5[i] == '\0') {
		printf("str3 == str5");
	}

	j = strcmp(str3, str5);
	if (j == 0) {
		printf("相等\n");
	} else if(j > 0) {
		printf("str3大\n");
	} else {
		printf("str5大\n");
	}


	return 0;
}

