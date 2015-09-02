#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define NUMLINES 10

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

/* tail -n: print the last n lines of the input */
int main(int argc, char *argv[])
{
	int numlines = NUMLINES;
	char c;

	/* argument handling */
	while (--argc > 0 && (*++argv)[0] == '-') {
		c = *(*argv+1);
		if (isdigit(c)) {
			numlines = atoi(*argv+1);
			if (numlines <= 0) {
				printf("\nillegal value\n");
				argc = -1;
			}
		} else {
			printf("\ntail: illegal option %c\n", c);
			argc = -1;
		}
	}
	if (argc != 0) {
		printf("Usage: tail -n");
	} else {
		char *lineptr[numlines]; /* pointers to saved lines */

		/* body of program */
		printf("\nDisplaying last %d lines\n", numlines);
		readlines(lineptr, numlines);
		writelines(lineptr, numlines);
	}
	printf("\n\n");
	return 0;
}

#define MAXLEN 1000
int my_getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int numlines)
{
	int len, nlines = 0;
	char *p, line[MAXLEN];

	while ((len = my_getline(line, MAXLEN)) > 0) {
		if ((p = alloc(len)) == NULL) {
			return -1;
		} else if (nlines >= numlines) {
			/* handle overflow */
			for(int i = 0; i < numlines-1; i++) {
				lineptr[i] = lineptr[i+1];
			}
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines-1] = p;
		} else {
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	if (nlines < numlines) {
		lineptr[nlines] = NULL;
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++) {
		if (!lineptr[i])
			break;
		else
			printf("%s\n", lineptr[i]);
	}
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	} else {
		return 0;
	}
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

int my_getline(char s[], int lim)
{
	int c, i;

	for(i=0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
