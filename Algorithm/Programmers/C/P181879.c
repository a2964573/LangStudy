// 정수가 담긴 리스트 num_list가 주어질 때, 
// 리스트의 길이가 11 이상이면 리스트에 있는 모든 원소의 합을 10 이하이면 
// 모든 원소의 곱을 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// num_list_len은 배열 num_list의 길이입니다.
int solution(int num_list[], size_t num_list_len) {
    int answer = 0;
    int pos;
    
    if(num_list_len > 10){
        for(pos = 0; pos < num_list_len; pos++){
            answer += num_list[pos];
        }
    } else{
        answer++;
        
        for(pos = 0; pos < num_list_len; pos++){
            answer *= num_list[pos];
        }
    }
    
    return answer;
}