#include <stdio.h>

void escape(char s[], char t[])
{
	int i = 0;
	int j = 0;

	while (s[i] != '\0') {
	       switch(s[i]) {
		       case '\a':
			       t[j++] = '\\';
			       t[j++] = 'a';
			       i++;
			       break;
		       case '\b':
			       t[j++] = '\\';
			       t[j++] = 'b';
			       i++;
			       break;
		       case '\f':
			       t[j++] = '\\';
			       t[j++] = 'f';
			       i++;
			       break;
		       case '\n':
			       t[j++] = '\\';
			       t[j++] = 'n';
			       i++;
			       break;
		       case '\r':
			       t[j++] = '\\';
			       t[j++] = 'r';
			       i++;
			       break;
		       case '\t':
			       t[j++] = '\\';
			       t[j++] = 't';
			       i++;
			       break;
		       case '\v':
			       t[j++] = '\\';
			       t[j++] = 'v';
			       i++;
			       break;
		       case '\\':
			       t[j++] = '\\';
			       t[j++] = '\\';
			       i++;
			       break;
		       case '\?':
			       t[j++] = '\\';
			       t[j++] = '?';
			       i++;
			       break;
		       case '\'':
			       t[j++] = '\\';
			       t[j++] = '\'';
			       i++;
			       break;
		       case '\"':
			       t[j++] = '\\';
			       t[j++] = '\"';
			       i++;
			       break;
		       default:
			       t[j++] = s[i++];
			       break;
	       }
	}
	t[j] = '\0';
}

void descape(char s[], char t[])
{
	int i = 0;
	int j = 0;

	while (s[i] != '\0'){
		if (s[i] == '\\') {
			switch (s[++i]) {
				case 'a':
					t[j++] = '\a';
					break;
				case 'b':
					t[j++] = '\b';
					break;
				case 'f':
					t[j++] = '\f';
					break;
				case 'n':
					t[j++] = '\n';
					break;
				case 'r':
					t[j++] = '\r';
					break;
				case 't':
					t[j++] = '\t';
					break;
				case 'v':
					t[j++] = '\v';
					break;
				case '\\':
					t[j++] = '\\';
					break;
				case '?':
					t[j++] = '\?';
					break;
				case '\'':
					t[j++] = '\'';
					break;
				case '\"':
					t[j++] = '\"';
					break;
				default:
					t[j++] = '\\';
					t[j++] = s[i];
					break;
			}
			i++;
		}
		else
			t[j++] = s[i++];
	}
	t[j] = '\0';
}

int main()
{
	char s[] = "no tab here\t ok?";
	char t[20];

	escape(s, t);

	printf("\n%s", s);
	printf("\n%s", t);

	printf("\n");

	descape(t, s);

	printf("\n%s", t);
	printf("\n%s", s);

	printf("\n\n");
}

