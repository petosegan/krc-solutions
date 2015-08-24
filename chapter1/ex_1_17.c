#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */
#define MINLINE 80       /* minimum line size to print */

int my_getline(char line[], int maxline);

/* print all lines longer than 80 characters*/
int main()
{
	int len;	/* current line length */
	char line[MAXLINE]; /* current input line */

	while ((len = my_getline(line, MAXLINE)) > 0)
		if (len > MINLINE) {
			printf("%s", line);
		}
	return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim)
{
	int c, i;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
		if (i < lim - 1)
        		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
