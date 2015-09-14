#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

/* undef: remove a name and definition fom the table */
void undef(char *name)
{
	struct nlist *np;
	struct nlist *target;

	for (np = hashtab[hash(name)]; np != NULL; np = np->next) {
		if (strcmp(name, np->name) == 0) { /* found name first */
			hashtab[hash(name)] = NULL;
		} else if (strcmp(name, np->next->name) == 0) {
			target = np->next;
			np->next = target->next;
		}
	}
}

#define MAXLINE 100
#define MAXCHAR 100

int isdefine (char *, char *, char *);
int my_getline(char s[], int lim);
char *getword(char *startptr, char *word, int lim);
void replace_word(char line[], char *start, char *end, char defn[]);

/* simple version of C preprocessor */
int main()
{
	/* get a line
	 * check if it is a define line
	 * if so: install definition
	 * if not: check for defined names and replace
	 * print line */

	char line[MAXLINE]; /* holds the line under consideration */
	char name[MAXCHAR];
	char defn[MAXCHAR];
	struct nlist *np;
	int line_length = MAXLINE;

	char word[MAXCHAR]; /* holds the word under consideration */
	char *wordptr, *wordendptr;


	while (line_length > 0) {
		line_length = my_getline(line, MAXCHAR);
		/*printf("raw line:\t%s\n", line);*/
		if (isdefine(line, name, defn)) {
		/*	printf("found define statement\n");
		*	printf("name:\t%s\n", name);
		*	printf("defn:\t%s\n", defn); */
			install(name, defn);
		}
		else {
			wordptr = line;
			/*printf("no define found\n");*/
			while (*wordptr != '\n' && *wordptr != EOF && (wordptr - line) < MAXLINE) {
				wordendptr = getword(wordptr, word, MAXCHAR);
				/*printf("%s\n", word);*/
				np = lookup(word);
				if (np != NULL) {
					replace_word(line, wordptr, wordendptr, defn);
					wordendptr = wordptr + strlen(defn) + 1;
				}
				wordptr = wordendptr;
			}
			/* printf("processed line:\t%s\n", line);*/
		}
		printf("%s", line);
	}
	return 0;
}

int isdefine(char *line, char *name, char *defn)
{
	char *name_ptr = line;
	char *defn_ptr = line;
	char *end_ptr = line;
	if (strncmp(line, "#define", 7) == 0) {
	/*	printf("found #define\n");*/
		name_ptr += 7; /* skip #define */
		while (isspace(*(name_ptr++))) /* scan to beginning of name */
			;
		name_ptr -= 1; /* rollback to first character of name */
/*		printf("found name\n");*/
		defn_ptr = name_ptr;
		while (!isspace(*(defn_ptr++))) /*scan to end of name */
			;
		defn_ptr -= 1;
		*(defn_ptr++) = '\0'; /* terminate name */
		while (isspace(*(defn_ptr++)))
			;
		defn_ptr -= 1; /* rollback to first character of definition */
/*		printf("found defn\n");*/
		end_ptr = defn_ptr;
		while (*(end_ptr++) != '\n')
			;
		end_ptr -= 1;
/*		printf("found end\n");*/
		*end_ptr = '\0'; /* terminate definition */

		strcpy(name, name_ptr);
		strcpy(defn, defn_ptr);

		return 1;
	} else {
		return 0;
	}
}

/* my_getline: get line into s, return length */
int my_getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* getword: put next word or character following start pointer into word*/
char *getword(char* startptr, char *word, int lim)
{
	char *w = word;
	char *s = startptr;

	while (isspace(*s))
		s++;
	if (*s != EOF)
		*(w++) = *s;
	if (!isalpha(*s) && *s != '_') {
		*w = '\0';
		return s+1;
	}
	s++;
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = *(s++)) && *w != '_') {
			break;
		}
	*w = '\0';
	return s;
}

void replace_word(char line[], char *start, char *end, char defn[])
{
	char endbuffer[MAXLINE];

	strcpy(endbuffer, (end-1));

	strcpy(start, defn);

	strcat(line, " ");
	strcat(line, endbuffer);
}
