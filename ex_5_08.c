#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (month <=0 || month > 12) {
		printf("\nInvalid Month");
		return -1;
	}

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	if (day <= 0 || day > daytab[leap][month]) {
		printf("\nInvalid Day");
		return -1;
	}
	for (i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

	if (yearday <= 0 || yearday > (365 + leap)){
		printf("\nInvalid Day of Year");
	}
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main()
{

	int month;
	int day;

	printf("\n%d should be 1", day_of_year(2014, 1, 1));
	month_day(2014, 1, &month, &day);
	printf("\n%d, %d should be 1, 1", month, day);
	day_of_year(2014, 13, 1);
	day_of_year(2014, 1, 44);
	month_day(2014, 400, &month, &day);
	printf("\n\n");
}
