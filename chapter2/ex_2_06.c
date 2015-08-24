#include <stdio.h>

/* setbits: return x with the n bits beginning at position p (indexed from right) set to the rightmost n bits of y, leaving the other bits unchanged */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{

	unsigned zero_mask, clean_x, y_mask, y_bits;

	/* zero out the target bits in x */
	printf("%o ", x);
	zero_mask = ~(~(~0 << n) << p);
	printf(" %o ", zero_mask);
	clean_x = x & zero_mask;
	printf(" %o ", clean_x);

	/* fetch rightmost n bits of y */
	y_mask = ~(~0 << n);
	y_bits = (y & y_mask) << p;

	return (y_bits | clean_x);
}

int main()
{
	unsigned const TESTNUM = 0177;
	unsigned const SOURCENUM = 0106;

	printf("\n%o\n\n", setbits(TESTNUM, 5, 1, SOURCENUM));
}
