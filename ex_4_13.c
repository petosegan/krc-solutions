#include <stdio.h>
#include <string.h>

void reverse_recursor(char s[], int i, int j)
{
	char temp;
	if (i < j)
	{
		reverse_recursor(s, i+1, j-1);
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

void reverse_recursive(char s[])
{
	int i, j;
	i = 0;
	j = strlen(s) - 1;

	reverse_recursor(s, i, j);
}

int main()
{
	char test_string[] = "abcdefgh";
	char test_string2[] = "ijklmno";
	printf("\n%s", test_string);
	reverse_recursive(test_string);
	printf("\n%s", test_string);
	reverse_recursive(test_string);
	printf("\n%s", test_string);

	printf("\n\n%s", test_string2);
	reverse_recursive(test_string2);
	printf("\n%s", test_string2);
	printf("\n\n");
}
