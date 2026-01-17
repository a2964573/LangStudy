#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int get_random(int* rarr, int len)
{
	srand(time(NULL));

	int value = 0;
	int count = 0;
	int flag  = 0;
	int idx   = 0;
	int ridx;
	while(idx < len) {
		value = rand() % len + 1;

		flag = 0;
		for(ridx = 0; ridx < count; ridx++) {
			if(rarr[ridx] == value) {
				flag = 1;
				break;
			}
		}

		if(flag == 1) {
			continue;
		}

		rarr[idx] = value;
		count++;
		idx++;
	}

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

int main(int argc, char* argv[])
{
	// int arr[] = {5, 3, 8, 4, 2, 7, 1, 10, 9, 6, 18, 15, 16, 17, 13, 12, 11, 19, 14, 20};
	int arr[] = {5, 3, 8, 4, 2};
	int len = sizeof(arr) / sizeof(arr[0]);

	int lcnt = 0;

	int* rarr = (int*)malloc(sizeof(arr));

	clock_t s_time;
	clock_t e_time;
	double elapsed;

	s_time = clock();
	{
		int flag = 0;
		int max  = 0;
		int rnum;
		int temp;
		int idx;
		int idx2;
		while(1) {
			flag = 1;

			memset(rarr, 0x00, sizeof(arr));
			get_random(rarr, len);

			for(idx = 0; idx < len; idx++) {
				rnum = rarr[idx];

				temp      = arr[idx ];
				arr[idx ] = arr[rnum];
				arr[rnum] = temp;
			}

			for(idx = (len - 1); idx > 0; idx--) {
				max = arr[idx];

				for(idx2 = 0; idx2 < idx; idx2++) {
					if(arr[idx2] > max) {
						flag = 0;
						break;
					}
				}
			}

			if(flag == 1) {
				break;
			}

			lcnt++;
		}
	}
	e_time = clock();

	arr_print(arr, len);

	elapsed = (double)(e_time - s_time) / CLOCKS_PER_SEC;
	printf("Loop count: %d, Elapsed time: %.6f seconds\n", lcnt, elapsed);

	free(rarr);
    return 0;
}

