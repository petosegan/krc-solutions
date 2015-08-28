#include <stdio.h>
#include <string.h>
#include <time.h>

#define ALLOCSIZE 10000
#define MAXLINES 5000
#define MAXLEN 1000

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

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
int readlines_fast(char *lineptr[], int nlines, char storage[]);
void writelines(char *lineptr[], int nlines);

void my_qsort(char *lineptr[], int left, int right);

double time_readlines(void)
{
	int nlines;

	clock_t begin, end;
	double time_spent;
	char storage[MAXLINES * MAXLEN];

	begin = clock();

	if ((nlines = readlines_fast(lineptr, MAXLINES, storage)) >= 0) {
		my_qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		end = clock();
		time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
		return time_spent;
	} else {
		printf("error: input too big to sort\n");
		return -1;
	}
}

/* int main()
{
	int numruns = 1000;
	double runtimes[numruns];
	double average_time = 0.0;
	int i;

	for (i = 0; i < numruns; i++)
	{
		runtimes[i] = time_readlines();
		average_time += runtimes[i];
	}
	average_time /= numruns;
	printf("\nAverage Time:\t%fsec", average_time);
	printf("\nRuns:\t%d", numruns);
	printf("\n\n");
}
*/

int main()
{
	printf("\nRuntime:\t%f sec", time_readlines());
	printf("\n\n");
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

int readlines_fast(char *lineptr[], int maxlines, char storage[])
{
	int len, nlines, i;
	char line[MAXLEN];
	
	i = 0;
	nlines = 0;

	while ((len = my_getline(line, MAXLEN)) > 0) {
		if (nlines >=maxlines)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(&storage[i], line);
			lineptr[nlines++] = &storage[i];
			i += MAXLEN;
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

void my_qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	my_qsort(v, left, last-1);
	my_qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
