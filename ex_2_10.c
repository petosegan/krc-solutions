#include <stdio.h>

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int main()
{
	printf("\n%c", lower('B'));
	printf("\nshould be b");

	printf("\n%c", lower('f'));
	printf("\nshould be f");

	printf("\n\n");
}
