#include <stdio.h>
#include <string.h>
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



int main()
{
	char p[] = "12345";
	printf("\n%s", p);
	reverse(p);
	printf("\n%s", p);

	int num = -6789;
	itoa(num, p);
	printf("\n%d", num);
	printf("\n%s", p);

	printf("\n\n");
}
