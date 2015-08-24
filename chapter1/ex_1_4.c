#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for Celsius = 0, 20, ..., 300 */

int main()
{
	int fahr, celsius;
	int lower, upper, step;

	lower = 0; /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 20; /* step size */

	printf("Celsius\tFahrenheit\n");
	celsius = lower;
	while (celsius <= upper) {
		fahr = 9 * celsius / 5 + 32;
		printf("%d\t%d\n",  celsius, fahr);
		celsius = celsius + step;
	}

	return 0;
}
