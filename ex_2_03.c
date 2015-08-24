#include <stdio.h>
#include <ctype.h>

int htoi_digit(char cc)
{
	if (cc >= '0' && cc <= '9')
		return cc - '0';
	else if (cc >= 'a' && cc <= 'f')
		return cc - 'a' + 10;
	else if (cc >= 'A' && cc <='F')
		return cc - 'A' + 10;
	return -1;
}

int htoi(char s[])
{
	int ii, nn, ii_0;
	nn = 0;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		ii_0 = 2;
	else
		ii_0 = 0;

	for (ii=ii_0; isxdigit(s[ii]); ++ii)
		nn = 16 * nn + htoi_digit(s[ii]);
	return nn;
}

int main()
{
	printf("\n%d\n", htoi("aaa"));
	printf("\n%d\n", htoi("0xaaa"));
}
