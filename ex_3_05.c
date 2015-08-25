#include <stdio.h>
#include <string.h>

void reverse(char s[])
{
    int length = strlen(s) ;
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
char char_digit(int n)
{
	if (n >= 0 && n <= 9)
		return (n + '0');
	else if (n >= 10 && n <= 36)
		return (n - 10 + 'A');
	else
		return -1;
}

void itob(int n, char s[], int b)
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = char_digit(n % b);
	} while ((n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main()
{
	char answer[100];
	itob(7, answer, 2);
	printf("\n%s", answer);
	printf("\nshould be:\n111");
	itob(18, answer, 16);
	printf("\n\n%s", answer);
	printf("\nshould be:\n12");
	itob(26, answer, 16);
	printf("\n\n%s", answer);
	printf("\nshould be:\n1A");

	printf("\n\n");
}
