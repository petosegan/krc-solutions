#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MATH_COMMAND '#'

int getop(char []);
void push(double);
double pop(void);
void clear(void);

int main()
{
	int type;
	double op1, op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case MATH_COMMAND:
				if (strcmp(s, "msin") == 0)
					push(sin(pop()));
				else if (strcmp(s, "mpow") == 0) {
					op2 = pop();
					push(pow(pop(), op2));
				}
				else if (strcmp(s, "mexp") == 0)
					push(exp(pop()));
				else
					printf("error: unknown math command %s", s);
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

int getop(char s[])
{
	int i, c;
	int math_command = 0;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != 'm')
		return c;
	i = 0;
	if (c == '-')
		while (isdigit(s[++i] = c = getch()))
			;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == 'm') {
		math_command = 1;
		while (isalpha(s[++i] = c = getch()))
			;
	}
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	if (strcmp(s, "-") == 0)
		return '-';
	else if (strcmp(s, "m") == 0) {
		math_command = 0;
		return 'm';
	}
	else if (math_command == 1) {
		return MATH_COMMAND;
	}
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
