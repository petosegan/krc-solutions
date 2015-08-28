#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char *, char []);
void push(double);
double pop(void);
void clear(void);

/* expr: evaluate reverse Polish notation expression from the command line */
int main(int argc, char *argv[])
{
	int type;
	double op1, op2;
	char s[MAXOP];

	while (--argc > 0 && (type = getop(*++argv, s)) != EOF) {
		printf("\n%c", type);
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '%':
				op2 = pop();
				push(fmod(pop(), op2));
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			case 'd':
				op1 = pop();
				push(op1);
				push(op1);
				break;
			case 's':
				op1 = pop();
				op2 = pop();
				push(op1);
				push(op2);
				break;
			case 'p':
				op1 = pop();
				printf("\t%.8g\n", op1);
				push(op1);
				break;
			case 'c':
				clear();
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	printf("\n\n");
	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}
void clear(void)
{
	sp = 0;
}
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char *a, char s[])
{
	int c;

	while ((s[0] = c = *a) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	if (c == '-')
		while (isdigit(*(s++) = c = *(a++)))
			;
	if (isdigit(c))
		while (isdigit(*(s++) = c = *(a++)))
			;
	if (c == '.')
		while (isdigit(*(s++) = c = *(a++)))
			;
	*s = '\0';
	if (strcmp(s, "-") == 0)
		return '-';
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
