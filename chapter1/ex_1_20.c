#include <stdio.h>

#define MAXLINE 1000
#define COL_WIDTH 8

void detab(char from[], char to[]);
int my_getline(char s[], int lim);

/* replace tabs in input with appropriate number of spaces */
int main()
{
	int len;
	char line[MAXLINE];
	char line_detabbed[MAXLINE];

	while ((len=my_getline(line, MAXLINE)) > 0){
		detab(line, line_detabbed);
		printf("%s", line_detabbed);
	}
	return 0;
}

int my_getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim - 1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void detab(char from[], char to[])
{
	int i_from;
	int i_to;

	i_from = 0;
	i_to = 0;

	int dist_to_tab = 0;

	while(from[i_from] != '\0'){
		if (from[i_from] != '\t'){
			to[i_to] = from[i_from];
			i_to++;
			i_from++;
		}
		else {
			dist_to_tab = COL_WIDTH - i_to % COL_WIDTH;
			while(dist_to_tab > 0){
				to[i_to] = ' ';
				i_to++;
				dist_to_tab--;
			}
			i_from++;
		}

	}
	to[i_to] = '\0';
}
