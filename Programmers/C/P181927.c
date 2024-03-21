// 정수 리스트 num_list가 주어질 때, 
// 마지막 원소가 그전 원소보다 크면 마지막 원소에서 그전 원소를 뺀 값을 
// 마지막 원소가 그전 원소보다 크지 않다면 마지막 원소를 두 배한 값을 
// 추가하여 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// num_list_len은 배열 num_list의 길이입니다.
int* solution(int num_list[], size_t num_list_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * (num_list_len + 1));
    
    int pos;
    for(pos = 0; pos < num_list_len; pos++){
        answer[pos] = num_list[pos];
    }
    
    if(answer[num_list_len - 2] < answer[num_list_len - 1]){
        answer[num_list_len] = answer[num_list_len - 1] - answer[num_list_len - 2];
    }else{
        answer[num_list_len] = answer[num_list_len - 1] * 2;
    }
    
    return answer;
}