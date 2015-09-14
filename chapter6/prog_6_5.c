#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

int getword(char*, int);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);

int main()
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0])) {
			printf("%s\n", word);
			root = addtree(root, word);
		}
	treeprint(root);
	return 0;
}

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void);
char *my_strdup(char *);

/*addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = my_strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

/*treeprint in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *my_strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p,s);
	return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	int last_c = 0;

	while (isspace(c = getch()))
		last_c = c;
	while (c == '#') {
		while((c = getch()) != '\n') {
			last_c = c; /* skip preprocessor control lines */
		}
		while (isspace(c = getch()))
			last_c = c;
	}
	if (c == '\\') {
		while ((c = getch())) {
			if (c == '\"')
				break;
			last_c = c;
		}
		while (isspace(c = getch()))
			last_c = c;
	}
	if (c == '\"') {
		while ((c = getch())) {
			if (last_c != '\\' && c == '\"')
				break;
			last_c = c;
		} /* skip string constants */
		while (isspace(c = getch()))
			;
	}
	if (c == '/') {
		if ((c = getch()) == '*') {
			while ((c = getch())) {
				if (last_c == '*' && c == '/')
					break;
				last_c = c;
			}
		}
	} /* skip comments */

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0 ; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}


#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
