#include <stdio.h>

#define IN 1
#define OUT 0

#define TRUE 1
#define FALSE 0

int main()
{
	int cc, comment_state, saw_slash, saw_star, string_state;

	string_state = OUT;
	comment_state = OUT;
	saw_slash = FALSE;
	saw_star = FALSE;

	while ((cc = getchar()) != EOF) {
		if (comment_state == OUT) {
			if (cc == '/')
				saw_slash = TRUE;
			else if (saw_slash == TRUE) {
				if (cc == '*' && string_state == OUT) {
					comment_state = IN;
				}
				else {
					putchar('/');
					putchar(cc);
				}
				saw_slash = FALSE;
			}
			else {
				putchar(cc);
			}
			if (cc == '"'){
				if (string_state==OUT)
					string_state = IN;
				else
					string_state = OUT;
			}
		}
		else {
			if (cc == '*')
				saw_star = TRUE;
			else if (saw_star == TRUE) {
				if (cc == '/') {
					comment_state = OUT;
				}
				saw_star = FALSE;
			}
		}
	}
}

