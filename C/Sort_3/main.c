#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name [30];
} Person;

int compare(const void* firstData, const void* secondData){
    printf("11 | >> firstData: %d, secondData: %d\n", firstData, secondData);
    Person* fData = (Person*) firstData;
    Person* sData = (Person*) secondData;
    printf("14 | >> fData->age: %d, sData->age: %d\n", fData->age, sData->age);

    printf("16 | Comparison Starting...\n");
    if(fData->age < sData->age){
        printf("18 | >> fData->age[%d] is smaller than sData->age[%d]\n", fData->age, sData->age);
        return -1;
    }

    if(fData->age > sData->age){
        printf("23 | >> fData->age[%d] is bigger than sData->age[%d]\n", fData->age, sData->age);
        return 1;
    }

    return 0;
}

int printArr(const Person* pArr, int len){
    for(size_t i = 0; i < len; i++){
        if(i == 0)
            printf("----------------------------------------------\n");
        printf("34 | >> age['%.2d'] | name['%s']\n", pArr[i].age, pArr[i].name);
        if(i == len - 1)
            printf("----------------------------------------------\n");
    }

    return 0;
}

void main(){
    Person pArr[] = {
        {21, "John"},
        {17, "Kim"},
        {9, "Choi"},
        {33, "Oh"},
        {21, "Park"}
    };
    
    int len = sizeof(pArr) / sizeof(Person);

    printArr(pArr, len);
    printf("54 | Sorting before print end\n");
    qsort(pArr, len, sizeof(Person), compare);
    printf("56 | Sorting after print start\n");
    printArr(pArr, len);

    return;
}