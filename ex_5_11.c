#include <stdio.h>

#define MAXLINE 1000
#define COL_WIDTH 8

void detab(char from[], char to[]);
void entab(char from[], char to[]);
int my_getline(char s[], int lim);

/* replace spaces in input with appropriate number of spaces and tabs */
int main(int argc, char *argv[])
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
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void detab(char *from, char *to)
{
	int dist_to_tab = 0;
	char *to_start = to;

	while(*from != '\0'){
		if (*from != '\t'){
			*(to++) = *(from++);
		}
		else {
			dist_to_tab = COL_WIDTH - (to - to_start) % COL_WIDTH;
			while(dist_to_tab > 0){
				*(to++) = ' ';
				dist_to_tab--;
			}
			from++;
		}

	}
	*to = '\0';
}
/* replace blank space with appropriate number of spaces and tabs
 * assumes no tabs in input */
void entab(char *from, char *to)
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
