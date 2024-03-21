// 정수 start_num와 end_num가 주어질 때, 
// start_num에서 end_num까지 1씩 감소하는 수들을 차례로 담은 리스트를 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int* solution(int start_num, int end_num) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * (start_num - end_num + 1));
    
    int pos;
    for(pos = 0; pos < start_num - end_num + 1; pos++){
        answer[pos] = start_num - pos;
    }
    
    return answer;
}