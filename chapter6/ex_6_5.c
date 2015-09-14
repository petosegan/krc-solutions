#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main()
{
	char *test_input = "MAXSIZE";
	char *test_output = "100";

	struct nlist *np;

	install(test_input, test_output);

	np = lookup(test_input);
	printf("%s\n", np->defn);
	undef(test_input);
	np = lookup(test_input);
	if (np != NULL)
		printf("%s\n", np->defn);
	else
		printf("not found\n");

	install(test_input, "200");
	np = lookup(test_input);
	if (np != NULL)
		printf("%s\n", np->defn);
	else
		printf("not found\n");
}
