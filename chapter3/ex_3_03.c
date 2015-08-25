#include <stdio.h>

void expand(char s[], char t[])
{
	int i = 0;
	int j = 0;
	int prev_char = -1;
	while (s[i] != '\0') {
		if (s[i] == '-' && prev_char != -1 && s[i+1] != '\0') {
			for (int k = prev_char + 1; k < s[i+1]; k++) {
				t[j++] = k;
			}
		}
		else
			t[j++] = s[i];
		prev_char = s[i];
		i++;
	}
	t[j] = '\0';
}

int main()
{
	char source[] = "a-b-c-z";
	char target[1000];

	expand(source, target);
	printf("\n%s", source);
	printf("\n%s", target);

	printf("\n\n");
}
