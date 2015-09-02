#include <stdio.h>

void my_strcat(char s[], char t[])
{
	int i,j;

	i = j = 0;

	while (s[i] != '\0')
		i++;
	while ((s[i++] = t[j++]) != '\0')
		;
}

void strcat_ptr(char *s, char *t)
{
	while (*s++ != '\0')
		;
	s -= 1; /* roll back to overwrite the terminator */
	while ((*s++ = *t++) != '\0')
		;
}

int main()
{
	char test_string1[100] = "bacon";
	char test_string2[100] = " and eggs";

	printf("\n%s", test_string1);
	printf("\n%s", test_string2);

	my_strcat(test_string1, test_string2);
	printf("\n%s", test_string1);

	char test_string3[100] = "peanut butter";
	char test_string4[100] = " and jelly";

	printf("\n%s", test_string3);
	printf("\n%s", test_string4);

	strcat_ptr(test_string3, test_string4);
	printf("\n%s", test_string3);

	printf("\n\n");
}
