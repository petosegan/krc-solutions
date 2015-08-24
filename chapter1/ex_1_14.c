#include <stdio.h>

#define NUM_CHARS 26

/* print a histogram of character frequencies */
int main()
{
	int ii, jj, cc;
	int char_freqs[NUM_CHARS];

	for (ii=0; ii < NUM_CHARS; ii++)
		char_freqs[ii] = 0;
        
	// march through input and update char_freqs
	while ((cc = getchar()) != EOF) {
		if (cc >= 'a' && cc <= 'z')
			++char_freqs[cc - 'a'];
		else if (cc >= 'A' && cc <= 'Z')
			++char_freqs[cc - 'A'];
	}

	// march through character list and display char freqs
	for (ii=0; ii < NUM_CHARS; ii++){
		printf("\n %c:\t", ii + 'a');
		for (jj = 0; jj < char_freqs[ii]; jj++){
			printf("#");
		}
	}
	printf("\n\n");

}
