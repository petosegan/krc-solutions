#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

void reverse(char *p)
{
	int c;
	char *q;
	q = p;

	while(*(q++) != '\0'){
		;
	}
	q -= 2;
	while(q > p) {
		c = *p;
		*(p++) = *q;
		*(q--) = c;
	}
}

void itoa(int n, char *p)
{
	int sign;
	char *q;
	q = p;

	if ((sign = n) < 0)
		n = -n;
	do {
		*(p++) = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		*(p++) = '-';
	*p = '\0';
	reverse(q);
}

int strindex(char *s, char *t)
{
	char *s_start = s;
	char *j, *k;

	while (*s != '\0') {
		for (j=s, k=t;*k != '\0' && *j==*k; j++, k++)
			;
		if (k > t && *k == '\0')
			return (s-s_start);
		s += 1;
	}
	return -1;
}

#define NUMBER 0

int getch(void);
void ungetch(int);

int getop(char *s)
{
	int c;

	while ((*s = c = getch()) == ' ' || c == '\t')
		;
	*(++s) = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	if (isdigit(c))
		while (isdigit(*(s++) = c = getch()))
			;
	if (c == '.')
		while (isdigit(*(s++) = c = getch()))
			;
	*s = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int main()
{

	int type;
	char s[100];
	type = getop(s);
	printf("\n%c", type);
	printf("\n%s", s);
	printf("\n\n");
}
