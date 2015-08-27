#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);

/* getfloat: get next float from input into *pn*/
int getfloat(double *pn)
{
	int c, sign;
	double power;

	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c); /* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		if (!isdigit(c = getch()) && c != '.') {
			ungetch(c);
			return 0;
		}
	}

	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}
	*pn *= sign / power;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main()
{
	int n;
	double array[SIZE];
	for (n = 0; n < SIZE; n++)
		array[n] = 0;
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;
	for (n = 0; n < SIZE; n++)
		printf("%f ", array[n]);
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
