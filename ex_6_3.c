#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXCHAR 100
#define MAXLINES 1000

int getword(char* word, int maxword, int *line);
struct tnode *addtree(struct tnode *p, char *word, int line);
void treeprint(struct tnode *treeptr);

/* print concordance of words and line numbers */
int main()
{
	struct tnode *root;
	char word[MAXCHAR];
	int startline = 1;
	int *line = &startline;
	

	root = NULL;
	while (getword(word, MAXWORD, line) != EOF)
		if (isalpha(word[0])) {
			root = addtree(root, word, *line);
		}
	treeprint(root);
	return 0;
}
struct tnode {
	char *word;
	int lines[MAXLINES];
	struct tnode *left;
	struct tnode *right;
};

struct tnode *talloc(void);
char *my_strdup(char *);
void addline(int (*lines)[MAXLINES], int line)
{
	int found = 0;
	int i = 0;
	for (; (*lines)[i] > 0; i++) {
	       if ((*lines)[i] == line)
		       found = 1;
	}
	if (!found) {
		(*lines)[i++] = line;
		(*lines)[i] = -1;
	}
}

/*addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int line)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = my_strdup(w);
		addline(&(p->lines), line);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		addline(&(p->lines), line);
	else if (cond < 0)
		p->left = addtree(p->left, w, line);
	else
		p->right = addtree(p->right, w, line);
	return p;
}

void printlines(int lines[MAXLINES])
{
	for (int i = 0; lines[i] > 0; i++)
		printf(" %d", lines[i]);
	printf("\n");
}

/*treeprint in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%s:", p->word);
		printlines(p->lines);
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
int getword(char *word, int lim, int *line)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch())) {
		*line += (c == '\n');
	}
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
