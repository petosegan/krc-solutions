#include <stdio.h>

#define IN 1
#define OUT 0

#define TRUE 1
#define FALSE 0

int main()
{
	int cc, comment_state, saw_slash, saw_star, string_state;
	int num_rparen, num_lparen, num_rbrace, num_lbrace, num_rbracket, num_lbracket;
	num_rparen = num_lparen = 0;
	num_rbrace = num_lbrace = 0;
	num_rbracket = num_lbracket = 0;

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
				saw_slash = FALSE;
			}
			if (cc == '\"' || cc == '\''){
				if (string_state==OUT)
					string_state = IN;
				else
					string_state = OUT;
			}
			if (comment_state==OUT && string_state==OUT){
				if (cc=='(')
					num_lparen++;
				else if (cc==')')
					num_rparen++;
				else if (cc=='[')
					num_lbracket++;
				else if (cc==']')
					num_rbracket++;
				else if (cc=='{')
					num_lbrace++;
				else if (cc=='}')
					num_rbrace++;
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
	if (num_lparen != num_rparen)
		printf("Parentheses are imbalanced!\n");
	if (num_lbrace != num_rbrace)
		printf("Braces are imbalanced!\n");
	if (num_lbracket != num_rbracket)
		printf("Brackets are imbalanced!\n");
}

