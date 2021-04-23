#include <stdio.h>

char *mystrncpy(char *dest, const char *src, size_t n);
char *mystrncat(char *dest, const char *src, size_t n);
int mystrcmp(const char *s1, const char *s2);
int main(void)
{
	char d[100] = "hello";
	char *s = "world";

	puts(mystrncat(d, s, 94));
	puts(mystrncpy(d, "good morning", 99));

	printf("%d\n", mystrcmp(d, s));

	return 0;
}

// 
char *mystrncpy(char *dest, const char *src, size_t n)
{
	int i;	

	for (i = 0; src[i] && i < n; i++) {
		dest[i] = src[i];
	}
	if (!src[i]) {
		dest[i] = '\0';
	}

	return dest;
#if 0
	char *ret = dest;

	while (*dest++ = *src++)
		;

	return ret;
#endif
}

char *mystrncat(char *dest, const char *src, size_t n)
{
	char *ret = dest;

	while (*dest)
		dest++;
	mystrncpy(dest, src, n);

	return ret;
}

int mystrcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2) {
		if (*s1 != *s2)
			break;
		s1 ++;
		s2 ++;
	}
	if (*s1 == '\0' && *s2 =='\0')
		return 0;
	return *s1 - *s2;
}



