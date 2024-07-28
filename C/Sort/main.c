#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int filter(int* arr, int step, int value){
    int index = 0;

    while(1){
        if(arr[index] == value) return -1;
        if(index == step ) return value;

        index++;
    }
}

int compare(const void* a, const void* b){
    int num1 = *(int*)a;
    int num2 = *(int*)b;

    if(num1 < num2) return 1;
    if(num1 > num2) return -1;

    return 0;
}

int printArr(int* arr, int len){
    for(size_t i = 0; i < len; i++){
        printf("%d", arr[i]);
        if(i != len - 1){
            printf(" | ");
        }
    }

    printf("\n");

    return 0;
}

void main(){
    int arr[10] = {0, };
    int len = sizeof(arr) / sizeof(arr[0]);

    srand(time(NULL));

    for(size_t i = 0; i < len; i++){
        int rtn = filter(arr, i, rand() % 10 + 1);

        if(rtn < 0){
            i--;
            continue;
        }

        arr[i] = rtn;
    }

    printArr(arr, len);

    qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]), compare);

    printArr(arr, len);

    return;
}