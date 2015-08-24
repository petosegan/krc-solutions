#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("Min Character Size:\t%d\n", CHAR_MIN);
	printf("Max Character Size:\t%d\n", CHAR_MAX);
	printf("Min Integer Size:\t%d\n", INT_MIN);
	printf("Max Integer Size:\t%d\n", INT_MAX);
	printf("Min Long Size:\t\t%ld\n", LONG_MIN);
	printf("Max Long Size:\t\t%ld\n", LONG_MAX);
	printf("Min Short Size:\t\t%d\n", SHRT_MIN);
	printf("Max Short Size:\t\t%d\n", SHRT_MAX);
	printf("Max UCharacter Size:\t%u\n", UCHAR_MAX);
	printf("Max UInteger Size:\t%u\n", UINT_MAX);
	printf("Max ULong Size:\t\t%lu\n", ULONG_MAX);
	printf("Max UShort Size:\t%u\n", USHRT_MAX);
	return 0;
}
