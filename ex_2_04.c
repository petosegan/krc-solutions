#include <stdio.h>

void squeeze_all(char s[], char b[])
{
	int i, j, k;
	int badchar = 0;

	for (i = k = 0; s[i] != '\0'; i++)
	{
		badchar = 0;
		for (j=0; b[j] != '\0'; j++)
		{
			if (s[i] == b[j]){
				badchar = 1;
			}
		}
		if (badchar == 0)
		    s[k++] = s[i];
	}
	s[k] = '\0';
}

int main()
{
	char badchars[] = "abcd";
	char source[] = "hhahhbhhchhd";

	printf("\n%s\n", source);
	squeeze_all(source, badchars);
	printf("\n%s\n", source);
}
