#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) /* upper-lower: convert input case, depending on name called */
{
	int c;
	int (*converter)(int c);

	if (strcmp(argv[0], "./upper") == 0)
		converter = &toupper;
	else if (strcmp(argv[0], "./lower") == 0)
		converter = &tolower;
	else {
		printf("Error: program name %s not recognized\n", argv[0]);
		return -1;
	}

	while ((c = getchar()) != EOF)
		putchar((*converter)(c));
	return 0;
}
