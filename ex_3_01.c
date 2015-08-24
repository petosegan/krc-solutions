#include <stdio.h>

/* find x in sorted array v of length n*/
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1; /* no match */
}

/* find x in sorted array v of length n, using only one test in loop*/
int binsearch_fast(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high + 1) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid;
	}
        if (v[low] == x)
		return low;
	return -1; /* no match */
}

int main()
{
	int test_array[10];
	for (int i = 0; i < 10; i++)
	{
		test_array[i] = i;
	}

	printf("\n%d", binsearch_fast(3, test_array, 10));
	printf("\nshould be 3");

	printf("\n\n");
}
