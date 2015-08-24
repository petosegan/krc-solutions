#include <stdio.h>
#define MAXLINE 1000

int my_getline(char line[], int maxline);
void reverse(char to[], char from[], int len);

/* reverse inputs one line at a time */
int main()
{
	int len = 0;

	char line[MAXLINE];	/* current input line */
	char rev_line[MAXLINE]; /* reversed input line */

	while ((len = my_getline(line, MAXLINE)) > 0){
		reverse(rev_line, line, len);
		printf("%s", rev_line);
	}
	printf("\n");
	return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* reverse: put reversed copy of 'from' into 'to'; assume to is big enough */
void reverse(char to[], char from[], int len)
{
	int i;

	i = len;
	to[i] = '\0';

	while(i>=0){
		to[len - i - 1] = from[i];
		i--;
	}
}	
