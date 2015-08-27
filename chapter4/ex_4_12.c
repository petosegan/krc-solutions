#include <stdio.h>

int i = 0;

void itoa_recursor(int n, char s[])
{
	if (n / 10)
		itoa_recursor(n/10, s);
	s[i++] = (n % 10 + '0');
}

void itoa_recursive(int n, char s[])
{
	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
	if (n / 10)
		itoa_recursor(n/10, s);
	s[i++] = (n % 10 + '0');
	s[i] = '\0';
	i = 0;
}

int main()
{
	int test = -1234;
	int test2 = 5678;
	char test_string[100];

	itoa_recursive(test, test_string);
	printf("\n%d", test);
	printf("\n%s", test_string);
	itoa_recursive(test2, test_string);
	printf("\n\n%d", test2);
	printf("\n%s", test_string);
	printf("\n\n");
}
