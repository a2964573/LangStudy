// 정수 배열 arr와 자연수 k가 주어집니다.
// 만약 k가 홀수라면 arr의 모든 원소에 k를 곱하고, k가 짝수라면 arr의 모든 원소에 k를 더합니다.
// 이러한 변환을 마친 후의 arr를 return 하는 solution 함수를 완성해 주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// arr_len은 배열 arr의 길이입니다.
int* solution(int arr[], size_t arr_len, int k) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(arr_len);
    answer = arr;
    
    int pos;
    if(k % 2 == 0){
        for(pos = 0; pos < arr_len; pos++){
            answer[pos] += k;
        }
    }else{
        for(pos = 0; pos < arr_len; pos++){
            answer[pos] *= k;
        }
    }
    
    
    return answer;
}