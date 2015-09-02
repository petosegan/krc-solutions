#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 1000
#define COL_WIDTH 8

void detab(char from[], char to[], int tabstops[]);
void entab(char from[], char to[], int tabstops[]);
int my_getline(char s[], int lim);

/* replace spaces in input with appropriate number of spaces and tabs */
int main(int argc, char *argv[])
{
	int len, tab_offset = 0, tab_increment = COL_WIDTH;
	int tabstops[MAXLINE];
	char line[MAXLINE];
	char line_detabbed[MAXLINE];
	char line_entabbed[MAXLINE];
	char c;
	int i, j;

	/* parse command line options */

	while (--argc > 0 && (**++argv == '-' || **argv == '+')) {
		c = **argv;
		switch(c) {
			case '-':
				if (isdigit(*(*argv+1))) {
					tab_offset = atoi(*argv+1);
				} else {
					printf("\nerror: specify tab offset");
					argc = -1;
				}
				break;
			case '+':
				if (isdigit(*(*argv+1))) {
					tab_increment = atoi(*argv+1);
					if (tab_increment <= 0) {
						printf("\nerror: tab increment must be positive");
						argc = -1;
						break;
					}
				} else {
					printf("\nerror: specify tab increment");
					argc = -1;
				}
				break;
			default:
				printf("\nentab: illegal option %c\n", c);
				argc = -1;
				break;
		}
	}
	if (argc != 0) {
		printf("\nUsage: entab -m +n\n\n");
	} else {
		for(i = tab_offset, j = 0; i < MAXLINE; i+= tab_increment, j++) {
			tabstops[j] = i;
		}
		tabstops[j] = -1;

		while ((len=my_getline(line, MAXLINE)) > 0){
			detab(line, line_detabbed, tabstops); /* entab expects tabless input */
			entab(line_detabbed, line_entabbed, tabstops);
			printf("%s", line_entabbed);
		}
		return 0;
	}
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

void detab(char *from, char *to, int *tabstops)
{
	int next_tab = 0;
	char *to_start = to;

	while(*from != '\0'){
		if (*from != '\t')
			*(to++) = *(from++);
		else {
			while ((to-to_start) >= next_tab) {
				if (*tabstops >= 0)
					next_tab = *(tabstops++);
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

void entab(char *from, char *to, int *tabstops)
{
	int next_tab = 0, num_space = 0;
	char *from_start = from;


	while (*from != '\0') {
		if (*from != ' ') {
			while (num_space-- > 0) 
				*(to++) = ' ';
			num_space = 0;
			*(to++) = *(from++);
		}
		else {
			while((from - from_start) >= next_tab) {
				if (*tabstops >= 0)
					next_tab = *(tabstops++);
				else
					next_tab += COL_WIDTH;
			}
			if ((from++ - from_start) == next_tab - 1) {
				*(to++) = '\t';
				num_space = 0;
			} else 
				num_space++;
		}
	}
	*to = '\0';
}
