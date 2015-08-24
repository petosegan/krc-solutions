#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int my_getline(char line[], int maxline);

/* remove trailing blanks and tabs and delete blank lines*/
int main()
{
	int len;	/* current line length */
	char line[MAXLINE]; /* current input line */

	while ((len = my_getline(line, MAXLINE)) > 0)
		if (len > 1) {
			printf("%s", line);
		}
	return 0;
}

/* my_getline: read a line into s, delete trailing blanks and tabs, return length */
int my_getline(char s[], int lim)
{
	int c, i;
	int num_white = 0;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i){
		if (c == '\t' || c == ' ')
			num_white++;
		else
			num_white = 0;
		if (i < lim - 1)
        		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i-num_white] = '\0';
	return i-num_white;
}
