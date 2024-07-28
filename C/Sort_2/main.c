#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int shuffle(char* arr, int len){
    int ranNum, index = 0;
    char temp;

    for(size_t i = 1; i < len; i++){
        ranNum = rand() % len;

        temp = arr[index];
        arr[index] = arr[ranNum];
        arr[ranNum] = temp;
    }

    return 0;
}

int compare(const void* a, const void* b){
    char achar = *(char*) a;
    char bchar = *(char*) b;

    if(achar < bchar) return -1;
    if(achar > bchar) return 1;

    return 0;
}

int printArr(char* arr, int len){
    for(size_t i = 0; i < len; i++){
        printf("%c", arr[i]);
        if(i != len - 1){
            printf(" | ");
        }
    }
    printf("\n");

    return 0;
}

void main(){
    char arr[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    int len = sizeof(arr) / sizeof(arr[0]);

    srand(time(NULL));
    
    printArr(arr, len);
    shuffle(arr, len);
    printArr(arr, len);
    qsort(arr, len, sizeof(arr[0]), compare);
    printArr(arr, len);

    return;
}