#include <stdio.h>

int main()
{
	int c;
	int num_spaces;

	num_spaces = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			num_spaces++;
			if (num_spaces == 1)
				putchar(c);
		}
		else
		{
			num_spaces = 0;
			putchar(c);
		}
	}

	return 0;
}
