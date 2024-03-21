// 정수 리스트 num_list가 주어질 때, 
// 첫 번째로 나오는 음수의 인덱스를 return하도록 solution 함수를 완성해주세요. 음수가 없다면 -1을 return합니다.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// num_list_len은 배열 num_list의 길이입니다.
int solution(int num_list[], size_t num_list_len) {
    int answer = -1;
    int pos;
    
    for(pos = 0; pos < num_list_len; pos++){
        if(0 > num_list[pos]){
            answer = pos;
            break;
        }
    }
    
    return answer;
}