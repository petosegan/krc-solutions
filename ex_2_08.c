#include <stdio.h>

int get_intlen()
{
    int intlen = 0;
    unsigned all_ones = ~0;
    while (all_ones > 0)
    {
	all_ones >>= 1;
	intlen++;
    }    
    return intlen;
}



/* rightrot: return value of x rotated to right by n positions */
unsigned rightrot(unsigned x, int n)
{
	int intlen = get_intlen();

        unsigned upper_bits, lower_bits;

	upper_bits = x & (~0 << n);
	lower_bits = x & ~(~0 << n);

	return ((upper_bits >> n) | (lower_bits << (intlen - n)));
}

int main()
{

	unsigned const TESTNUM = 0177;
	printf("\n%o",rightrot(TESTNUM, 3));
	printf("\nshould be 34000000017");
	printf("\n%o",rightrot(TESTNUM, 2));
	printf("\nshould be 30000000037");

	printf("\n\n");
}
