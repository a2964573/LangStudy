#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int quick_sort(int* arr, int start, int end)
{
	if((start + 1) >= end) {
		return 0;
	}

	int cidx = start + 1;
	int pidx = start;
	int temp;
	for(; cidx < end; cidx++) {
		if(pidx == cidx) {
			continue;
		}

        if((pidx < cidx && arr[pidx] > arr[cidx]) ||
           (pidx > cidx && arr[pidx] < arr[cidx])) {
			temp      = arr[cidx];
			arr[cidx] = arr[pidx];
			arr[pidx] = temp;

			temp = cidx;
			cidx = pidx;
			pidx = temp;
		}
	}

	quick_sort(arr, start     , pidx);
	quick_sort(arr, (pidx + 1), end );

	return 0;
}

int arr_print(int* arr, int len)
{
	printf("[");
	for(int i = 0; i < len; i++) {
		printf("%d", arr[i]);

		if(i != (len - 1)) {
			printf(" ");
		}
	}
	printf("]\n");

	return 0;
}

int compare(const void* left_data, const void* right_data)
{
	int* lnum = (int*)left_data;
	int* rnum = (int*)right_data;

	if(lnum < rnum) {
		return -1;
	}
	else
	if(lnum > rnum) {
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	int arr1[] = {5, 3, 8, 4, 2, 7, 1, 10, 9, 6, 18, 15, 16, 17, 13, 12, 11, 19, 14, 20};
	int arr2[] = {5, 3, 8, 4, 2, 7, 1, 10, 9, 6, 18, 15, 16, 17, 13, 12, 11, 19, 14, 20};
	int len = (sizeof(arr1) / sizeof(arr1[0]));

	clock_t s_time;
	clock_t e_time;
	double elapsed;

	s_time = clock();
	{
		quick_sort(arr1, 0, len);
	}
	e_time = clock();

	arr_print(arr1, len);

	elapsed = (double)(e_time - s_time) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.6f seconds\n", elapsed);

	s_time = clock();
	{
		qsort(arr2, len, sizeof(arr1[0]), compare);
	}
	e_time = clock();

	arr_print(arr1, len);

	elapsed = (double)(e_time - s_time) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.6f seconds\n", elapsed);


    return 0;
}

