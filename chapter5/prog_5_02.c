#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn*/
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main()
{
	int n, array[SIZE];
	for (n = 0; n < SIZE; n++)
		array[n] = 0;
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;
	for (n = 0; n < SIZE; n++)
		printf("%d ", array[n]);
	printf("\n\n");
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
