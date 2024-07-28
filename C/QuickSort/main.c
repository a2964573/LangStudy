#include "main.h"

void main(){
    int arr [ARRAY_SIZE] = {0, };

    createArr(arr);
    printArr(arr);

    return;
}

int createArr(int* arr){
    int loopCount = 0;

    while(loopCount < ARRAY_SIZE){
        int rtn = createValue(arr, loopCount);

        if(rtn < 0){
            loopCount--;
            continue;
        }

        arr[loopCount++] = rtn;
    }

    return 0;
}

int createValue(int* arr, int loopMax){
    srand(time(NULL));

    int loopCount = 0;

    while(1){
        int value = rand() % ARRAY_MAX + 1;
        
        if(arr[loopCount] == value) return -1;
        if(loopCount == loopMax - 1) return value;

        loopCount++;
    }
}

int printArr(const int* arr){
    int loopCount = 0;
    while(loopCount < ARRAY_SIZE){
        printf("%d", arr[loopCount++]);
        printf(loopCount == ARRAY_SIZE ? "\n" : " | ");
    }

    return 0;
}