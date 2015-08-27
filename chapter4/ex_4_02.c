#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 100

int my_getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power, expval;
	int i, sign, exp_sign, exp;
	expval = 1.0;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++){
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E') {
		exp_sign = (s[++i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;
		for (exp = 0; isdigit(s[i]); i++)
			exp = 10 * exp + (s[i] - '0');
		exp *= exp_sign;
		expval = pow(10.0, exp);
	}

	return sign * val / power * expval;
}

/* rudimentary calculator */
int main()
{
	double sum, atof(char []);
	char line[MAXLINE];
	int my_getline(char line[], int max);

	sum = 0;
	while (my_getline(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof(line));
	return 0;
}
