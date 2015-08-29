#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define COL_WIDTH 8

void detab(char from[], char to[], char *tabstops[]);
void entab(char from[], char to[], char *tabstops[]);
int my_getline(char s[], int lim);

/* replace spaces in input with appropriate number of spaces and tabs */
int main(int argc, char *argv[])
{
	int len;
	char line[MAXLINE];
	char line_detabbed[MAXLINE];
	char line_entabbed[MAXLINE];

	while ((len=my_getline(line, MAXLINE)) > 0){
		detab(line, line_detabbed, argv);
		entab(line_detabbed, line_entabbed, argv);
		printf("%s", line_detabbed);
	}
	return 0;
}

int my_getline(char *s, int lim)
{
	int c;
	char *s_start = s;

	while ((c=getchar())!=EOF && c!='\n')
		*(s++) = c;
	if (c == '\n')
		*(s++) = c;
	*s = '\0';
	return (s - s_start);
}

void detab(char *from, char *to, char *tabstops[])
{
	int next_tab = 0;
	char *to_start = to;
	tabstops++; /*skip first argv */

	while(*from != '\0'){
		if (*from != '\t')
			*(to++) = *(from++);
		else {
			while ((to-to_start) > next_tab) {
				if (*tabstops)
					next_tab += atoi(*(tabstops++));
				else
					next_tab += COL_WIDTH;
			}
			while(next_tab > (to-to_start))
				*(to++) = ' ';
			from++;
		}
	}
	*to = '\0';
}
/* replace blank space with appropriate number of spaces and tabs
 * assumes no tabs in input */
void entab(char *from, char *to, char *tabstops[])
{
	int num_white = 0;
	char *from_start = from;

	while(*from != '\0'){
		/* four cases:
		 * non-space, not leaving space - just copy and move on
		 * non-space, leaving space - if tab boundary, add tab
		 *                            else, put back spaces
		 * space, not tab boundary - increment num_white
		 * space, tab boundary - insert tab, reset num_white */
		if (*from != ' '){
			if (num_white != 0) {
				if (((from - from_start) % COL_WIDTH) == 0)
					*(to++) = '\t';
				else {
					while(num_white-- > 0)
						*(to++) = ' ';
				}
				num_white = 0;
			}
			*(to++) = *(from++);
		}
		else {
			if (((from-from_start) % COL_WIDTH) != (COL_WIDTH - 1)) 
				num_white++;
			else {
				*(to++) = '\t';
				num_white = 0;
			}
			from++;
		}
	}
	*to = '\0';
}
