#include <stdio.h>
#include <time.h>


int quick_sort(int* arr, int start, int end)
{
    if((start + 1) >= end) {
        return 0;
    }

    int* pivot = arr + (end - 1);
    int* ldata = arr + start;
    int* rdata = arr + start;
    int temp;

    while(rdata < pivot) {
        if(*rdata < *pivot) {
            temp = *ldata;
            *ldata = *rdata;
            *rdata = temp;
            ldata++;
        }
        rdata++;
    }

    temp = *ldata;
    *ldata = *pivot;
    *pivot = temp;

    int pidx = ldata - arr;

    quick_sort(arr, start     , pidx);
    quick_sort(arr, (pidx + 1), end );

    return 0;
}

int main(int argc, char* argv[])
{
	int arr[] = {5, 3, 8, 4, 2, 7, 1, 10};
	int len = (sizeof(arr) / sizeof(arr[0]));

	clock_t s_time = clock();
	{
		quick_sort(arr, 0, len);
	}
	clock_t e_time = clock();

	printf("[");
	for(int i = 0; i < len; i++) {
		printf("%d", arr[i]);

		if(i != (len - 1)) {
			printf(" ");
		}
	}
	printf("]\n");
	printf("Elapsed time: %.6f seconds\n", ((double)(e_time - s_time) / CLOCKS_PER_SEC));

    return 0;
}

