#include <stdio.h>
#include <time.h>

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
	test_array[3] = 4;

	int result;
	int numruns = 1000;

	clock_t begin, end;
	double time_spent, time_spent_fast;

	begin = clock();
	for (int i = 0; i < numruns; i++)
		result = binsearch(3, test_array, 10);
	end = clock();
	time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("\n%f sec\tfor binsearch", time_spent);

	begin = clock();
	for (int i = 0; i < numruns; i++)
		result = binsearch_fast(3, test_array, 10);
	end = clock();
	time_spent_fast = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("\n%f sec\tfor binsearch_fast", time_spent_fast);

	printf("\n\n");

}
