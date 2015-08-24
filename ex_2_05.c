#include <stdio.h>

int any(char s[], char b[])
{
	int i, j;
	int charloc = -1;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j=0; b[j] != '\0'; j++)
		{
			if (s[i] == b[j] && charloc == -1){
				charloc = i;
			}
		}
	}
	return charloc;
}

int main()
{
	char badchars[] = "abcd";
	char source[] = "hhahhbhhchhd";

	printf("\n%s\n", source);
	printf("\n%d\n", any(source, badchars));
}
