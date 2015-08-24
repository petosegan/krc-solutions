#include <stdio.h>

/* bitcount: return the number of bits on in x */
int bitcount(unsigned x)
{
	int b = 0;
	while (x > 0)
	{
		x &= (x-1);
		b++;
	}
	return b;
}

int main()
{
	unsigned const TESTNUM = 0177;

	printf("\n%d", bitcount(TESTNUM));
	printf("\nshould be 7");

	printf("\n\n");
}
