#include "main.h"

struct info {
	int t_number: 3;
	int t_num;
};

int func(char* str)
{
	return atol(str);
}

int main()
{
/*
	struct info info_t = {0,};
	// info_t.t_num    = 2152000000;
	info_t.t_number = 7;
	info_t.t_num    = 7;

	// printf("%d:%d\n", info_t.t_number, info_t.t_num);
	printf("%d:%d\n", info_t.t_number, info_t.t_num);
*/
/*
	char trading_number[11] = {0,};
	sprintf(trading_number, "00000000638");
	printf("%.11s:%d\n", trading_number, func(trading_number));
*/

	int x = 5;
//  int *ptr = &x;
    int *ptr = NULL;
	ptr = &x;
    int **pptr = &ptr;

	
    printf("%p\n", &x);
    printf("%p\n", &ptr);
    printf("%p\n", &pptr);
	printf("------------------------\n");
    printf("%p\n", (void*)*&*&ptr);
	printf("------------------------\n");
    printf("%p\n", (void*)&ptr);
    printf("%p\n", (void*)*&ptr);
    printf("%p\n", (void*)&*&ptr);
    printf("%p\n", (void*)*&*&ptr);
	printf("------------------------\n");
    printf("%p\n", (void*)**&pptr);
	printf("------------------------\n");
    printf("%d\n\n", *&**pptr);

	printf("========================\n");
	printf("%p\n", &*&**&ptr);
	printf("------------------------\n");
	printf("%p\n", &ptr);
	printf("%p\n", *&ptr);
	printf("%p\n", **&ptr);
	printf("%p\n", &**&ptr);
	printf("%p\n", *&**&ptr);
	printf("========================\n");


/*
	char arr[] = {1, 2, 3, 4};
	char *ptr  = arr;

	printf("%p\n", arr);
	printf("%p\n", &arr);
	printf("%d\n", arr[1]);
	printf("%p\n", &arr[1]);
	printf("%d\n", *arr);
	printf("%d\n", *(arr + 1));
*/

	return 0;
}

