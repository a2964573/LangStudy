#include <stdio.h>


int quick_sort(int* arr, int len, int pivot)
{
	printf("[");
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");

	if(pivot >= len) {
		return 0;
	}

	int temp;
	int index = (pivot + 1);

	while(index < len) {
		if(arr[pivot] < arr[index]) {
			temp = arr[pivot];
			arr[pivot] = arr[index];
			arr[index] = temp;
			pivot = index;

			index--;
			continue;
		}

		index++;
	}

	quick_sort(arr, pivot, 0);
	quick_sort(arr, len, (pivot + 1));
	return 0;
}

int main(int argc, char* argv[])
{
	int arr[] = {5, 3, 8, 4, 2, 7, 1, 10};
	int len = (sizeof(arr) / sizeof(arr[0]));

	quick_sort(arr, len, 0);
	printf("[");
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");

    return 0;
}
