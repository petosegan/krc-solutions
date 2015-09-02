#include <stdio.h>
#include <string.h>

#define ALLOCSIZE 10000
#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right, int rev,
		int (*comp)(void *, void *));
int numcmp(char *, char *);
void reverse(char *lineptr[], int nlines);
void to_lower(char *line, char *line2);
int strcmp_lower(char *line, char *line2);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines;
	int numeric = 0;
	int rev = 1;
	int folding = 0;
	char c;

	while (--argc > 0 && (*++argv)[0] == '-') { 
		while ((c = *++argv[0])) {
			switch(c) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					rev = -1;
					break;
				case 'f':
					folding = 1;
					break;
				default:
					printf("sortlines: illegal option %c\n", c);
					argc = -1;
					break;
			}
		}
	}
	if (argc != 0)
		printf("Usage: sortlines -n -r");
	else {

		if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
			my_qsort((void **) lineptr, 0, nlines-1, rev,
					(int (*)(void*,void*))(numeric ? numcmp : (folding ? strcmp_lower : strcmp)));
			writelines(lineptr, nlines);
			return 0;
		} else {
			printf("input too big to sort\n");
			return 1;
		}
	}
}

int strcmp_lower(char *s1, char *s2)
{
	char a1[MAXLEN];
	char a2[MAXLEN];

	to_lower(s1, a1);
	to_lower(s2, a2);

	return strcmp(a1, a2);
}


/* to_lower: copy line to target, but with all characters in lower case */
void to_lower(char *line, char *target)
{
	while (*line) {
		if (*line <= 'Z' && *line >= 'A')
			*(target++) = *(line++) - 'A' + 'a';
		else 
			*(target++) = *(line++);
	}
	*target = '\0';
}

void reverse(char *lineptr[], int nlines)
{
	char temp[MAXLEN];
	char **end = lineptr + nlines;

	while (lineptr < end) {
		strcpy(temp, *lineptr);
		strcpy(*(lineptr++), *end);
		strcpy(*(end--), temp);
	}
}


void my_qsort(void *v[], int left, int right, int rev,
		int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) * rev < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	my_qsort(v, left, last-1, rev, comp);
	my_qsort(v, last+1, right, rev, comp);
}

#include <stdlib.h>

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int my_getline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len=my_getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i=0; i<nlines; i++)
		printf("%s\n", lineptr[i]);
}

int my_getline(char *p, int lim)
{
	int c;
	char *q;
	q = p;

	while((c=getchar()) != EOF && c != '\n')
	{
		*(q++) = c;
	}
	if (c == '\n') {
		*(q++) = c;
	}
	*q = '\0';
	return (q-p);
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}
