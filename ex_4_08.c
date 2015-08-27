#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MATH_COMMAND '#'
#define VARIABLE_COMMAND '&'

int getop(char []);
void push(double);
double pop(void);
void clear(void);
double var_get(char);
void var_set(char, double);

double recent;

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
			case VARIABLE_COMMAND:
				if (strncmp(s, "vs", 2) == 0)
					var_set(s[2], pop());
				else if (strncmp(s, "vg", 2) == 0)
					push(var_get(s[2]));
				else
					printf("error: unknown variable command %s", s);
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
				op1 = pop();
				printf("\t%.8g\n", op1);
				recent = op1;
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
				recent = op1;
				push(op1);
				break;
			case 'c':
				clear();
				break;
			case 'r':
				push(recent);
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
	int variable_command = 0;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != 'm' && c != 'v')
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
	if (c == 'v') {
		variable_command = 1;
		while (isalpha(s[++i] = c = getch()))
			;
	}
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	if (strcmp(s, "-") == 0)
		return '-';
	else if (math_command == 1) {
		return MATH_COMMAND;
	}
	else if (variable_command == 1) {
		return VARIABLE_COMMAND;
	}
	return NUMBER;
}


char buf;
int buf_set = 0;

int getch(void)
{
	char result;
	result = (buf_set > 0) ? buf : getchar();
	buf_set = 0;
	return result;
}

void ungetch(int c)
{
	if (buf_set > 0)
		printf("ungetch: too many characters\n");
	else {
		buf = c;
		buf_set = 1;
	}
}

char vars[26];

double var_get(char c)
{
	return vars[c - 'a'];
}

void var_set(char c, double d)
{
	vars[c - 'a'] = d;
}
