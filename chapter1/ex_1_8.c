#include <stdio.h>

int main()
{
	int c, nb, nt, nn;

	nb = 0;
	nt = 0;
	nn = 0;

	while((c = getchar()) != EOF)
	{
		if (c == '\n')
			++nn;
	        if (c == ' ')
			++nb;
		if (c == '\t')
			++nt;
	}

	printf("Blanks:\t\t%d\nTabs:\t\t%d\nNewlines:\t%d\n", nb, nt, nn);

	return 0;
}
