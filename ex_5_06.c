#include <stdio.h>
#define MAXLINE 100

int my_getline(char *p, int lim)
{
	int c;
	char *q;
	q = p;

	while((c=getchar()) != EOF && c != '\n')
	{
		*(q++) = c;
	}
	if (c == '\n') {
		*(q++) = c;
	}
	*q = '\0';
	return (q-p);
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
