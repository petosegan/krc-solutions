#include <stdio.h>

/* invert: return x with the n bits starting at position p (indexed from right) inverted */
unsigned invert(unsigned x, int p, int n)
{

	unsigned target_mask;

	/* make mask for target bits */
	target_mask = (~(~0 << n) << p);
	
	return (target_mask ^ x);
}

int main()
{
	unsigned const TESTNUM = 0177;

	printf("\n%o", invert(TESTNUM, 2, 2));
	printf("\nshould be 163");

	printf("\n%o", invert(TESTNUM, 3, 3));
	printf("\nshould be 107");

	printf("\n\n");
}
