#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX_LEN 20

/* print a histogram of word lengths */
int main()
{
	int ii, jj, c, nc, state;
	int len_freqs[MAX_LEN];

	for (ii=0; ii < MAX_LEN; ii++)
		len_freqs[ii] = 0;

	state = OUT;
	nc = 0;
	while ((c=getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			len_freqs[nc]++;
		        nc = 0;
			state = OUT;
		}
		else if (state == OUT) {
			state = IN;
			nc++;
		}
		else
			nc++;
	}

	for (ii=0; ii < MAX_LEN; ii++){
		printf("\n %d:\t", ii);
		for (jj = 0; jj < len_freqs[ii]; jj++){
			printf("#");
		}
	}
	printf("\n");

}
