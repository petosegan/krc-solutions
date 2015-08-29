#include <stdio.h>

#define MAXLINE 1000
#define COL_WIDTH 8

void detab(char from[], char to[]);
void entab(char from[], char to[]);
int my_getline(char s[], int lim);

/* replace spaces in input with appropriate number of spaces and tabs */
int main()
{
	int len;
	char line[MAXLINE];
	char line_detabbed[MAXLINE];
	char line_entabbed[MAXLINE];

	while ((len=my_getline(line, MAXLINE)) > 0){
		detab(line, line_detabbed);
		entab(line_detabbed, line_entabbed);
		printf("%s", line_entabbed);
	}
	return 0;
}

int my_getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim - 1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
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
		if (from[i_from] != '\t')
			to[i_to++] = from[i_from++];
		else {
			dist_to_tab = COL_WIDTH - i_to % COL_WIDTH;
			while(dist_to_tab-- > 0)
				to[i_to++] = ' ';
			i_from++;
		}

	}
	to[i_to] = '\0';
}
/* replace blank space with appropriate number of spaces and tabs
 * assumes no tabs in input */
void entab(char from[], char to[])
{
	int i_from;
	int i_to;

	i_from = 0;
	i_to = 0;

	int num_white = 0;

	while(from[i_from] != '\0'){
		/* four cases:
		 * non-space, not leaving space - just copy and move on
		 * non-space, leaving space - if tab boundary, add tab
		 *                            else, put back spaces
		 * space, not tab boundary - increment num_white
		 * space, tab boundary - insert tab, reset num_white */
		if (from[i_from] != ' '){
			if (num_white != 0) {
				if ((i_from % COL_WIDTH) == 0)
					to[i_to++] = '\t';
				else {
					while(num_white-- > 0)
						to[i_to++] = ' ';
				}
				num_white = 0;
			}
			to[i_to++] = from[i_from++];
		}
		else {
			if ((i_from % COL_WIDTH) != (COL_WIDTH - 1)) 
				num_white++;
			else {
				to[i_to++] = '\t';
				num_white = 0;
			}
			i_from++;
		}
	}
	to[i_to] = '\0';
}
