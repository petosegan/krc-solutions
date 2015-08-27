#include <stdio.h>
#define swap(T, X, Y) {T temp; temp = X; X = Y; Y = temp;}

int main()
{
	int a, b;
	a = 2;
	b = 5;
	printf("\n%d\t%d", a, b);
	swap(int, a, b);
	printf("\n%d\t%d", a, b);
	printf("\n\n");
}
