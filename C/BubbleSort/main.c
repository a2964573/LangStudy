#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int bubble_sort(int* arr, int end)
{
	end -= 1;
	if(end == 0) {
		return 0;
	}

	int cidx = 0;
	int nidx = 0;
	int temp;
	for(; cidx < end; cidx++) {
		nidx = cidx + 1;
		if(arr[cidx] > arr[nidx]) {
			temp      = arr[cidx];
			arr[cidx] = arr[nidx];
			arr[nidx] = temp;
		}
	}

	return bubble_sort(arr, end);
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

int main(int argc, char* argv[])
{
	int arr[] = {5, 3, 8, 4, 2, 7, 1, 10, 9, 6, 18, 15, 16, 17, 13, 12, 11, 19, 14, 20};
	int len = (sizeof(arr) / sizeof(arr[0]));

	clock_t s_time;
	clock_t e_time;
	double elapsed;

	s_time = clock();
	{
		bubble_sort(arr, len);
	}
	e_time = clock();

	arr_print(arr, len);

	elapsed = (double)(e_time - s_time) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.6f seconds\n", elapsed);

    return 0;
}

