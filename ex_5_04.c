#include <stdio.h>
#include <string.h>

/* strend: return 1 if string t occurs at the end of string s, and 0 otherwise */
/*int strend(char *s, char *t)
{
	while (*s++ != *t) {
		if (*s == '\0')
			return 0;  never found start of t 
	}
	s -= 1;
	while (*s++ == *t++) {
		printf("\n%c%c", *s, *t);
		if (*s == '\0' && *t == '\0')
			return 1;  s and t are the same to the end 
		if (*s == '\0' || *t == '\0')
			return 2;
	}
	return 3;
}*/

int strend(char *s, char *t)
{
	char *s_end;
	char *t_end;

	s_end = s + strlen(s);
	t_end = t + strlen(t);

	while (t_end >= t) {
		if (s_end < s)
			return 0;
		if (*(s_end--) != *(t_end--)) {
			return 0;
		}
	}
	return 1;
}

int main()
{
	char test_string1[100] = "bacon";
	char test_string2[100] = "I love bacon";

	printf("\n%s", test_string1);
	printf("\n%s", test_string2);

	printf("\n%d", strend(test_string2, test_string1));

	char test_string3[100] = "peanut butter";
	char test_string4[100] = "peanut butter and jelly";

	printf("\n%s", test_string3);
	printf("\n%s", test_string4);

	printf("\n%d", strend(test_string4, test_string3));

	printf("\n\n");
}
