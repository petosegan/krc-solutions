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

void itoa(int n, char s[], int w)
{
	int i, j, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	j = w;
	do {
		s[i++] = n % 10 + '0';
		j--;
	} while ((n /= 10) > 0);
	if (sign < 0){
		s[i++] = '-';
		j--;
	}
	while (j-- > 0)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}

int main()
{
	char answer[1000];

	itoa(100, answer, 3);
	printf("\n%s", answer);
	printf("\nshould be\n100\n");

	itoa(100, answer, 5);
	printf("\n%s", answer);
	printf("\nshould be\n  100\n");

	printf("\n\n");
}
