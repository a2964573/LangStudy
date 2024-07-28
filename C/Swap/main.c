#include <stdio.h>

int swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

int main(){
    int a, b;

    a = 1;
    b = 2;

    printf("swapping before a: %d, b: %d\n", a, b);

    swap(&a, &b);

    printf("swapping after a: %d, b: %d\n", a, b);

    int* x, y = 1;

    x = &y;


    printf("%d, %d, %d", *x, x, &x);


    return 0;
}