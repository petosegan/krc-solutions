#include <stdio.h>
#define MAXLINE 100

int my_getline(char *p, int lim)
{
	int c, i;

	printf("\nfinished declarations\n");

	for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
	{
		*(p+i) = c;
	}
	if (c == '\n') {
		*(p+(i++)) = c;
	}
	*(p+i) = '\0';
	return i;
}

int main()
{
	char p[MAXLINE];
	int len;

	len = my_getline(p, MAXLINE);
	printf("\n%s", p);
	printf("\n%d", len);
	printf("\n\n");
}
