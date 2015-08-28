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

int atoi(char *s)
{
	int n;

	n = 0;
	while (*s >= '0' && *s <= '9')
		n = 10 * n + (*(s++) - '0');
	return n;
}

int main()
{
	char p[] = "1234";
	int num;


	num = atoi(p);
	printf("\n%s", p);
	printf("\n%d", num);
	printf("\n\n");
}
