// 정수 배열 arr가 주어집니다. arr의 각 원소에 대해 값이 50보다 크거나 같은 짝수라면 2로 나누고, 50보다 작은 홀수라면 2를 곱합니다. 
// 그 결과인 정수 배열을 return 하는 solution 함수를 완성해 주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// arr_len은 배열 arr의 길이입니다.
int* solution(int arr[], size_t arr_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(arr[0]) * arr_len);
    
    int pos;
    
    for(pos = 0; pos < arr_len; pos++){
        if(arr[pos] < 50 && arr[pos] % 2 == 1){
            answer[pos] = arr[pos] * 2;
        }else if(arr[pos] >= 50 && arr[pos] % 2 == 0){
            answer[pos] = arr[pos] / 2;
        }else{
            answer[pos] = arr[pos];    
        }
    }
    
    return answer;
}