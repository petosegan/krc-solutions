#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */

int fahr2cels(int temp_fahr);

int main()
{
	int fahr, celsius;
	int lower, upper, step;

	lower = 0; /* lower limit of temperature table */
	upper = 300; /* upper limit */
	step = 20; /* step size */

	printf("Fahrenheit\tCelsius\n");
	fahr = lower;
	while (fahr <= upper) {
		celsius = fahr2cels(fahr);
		printf("%d\t\t%d\n", fahr, celsius);
		fahr = fahr + step;
	}

	return 0;
}

int fahr2cels(int temp_fahr)
{
	int temp_cels;
	temp_cels = 5 * (temp_fahr - 32) / 9;
	return temp_cels;
}
