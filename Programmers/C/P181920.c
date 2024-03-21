// 정수 start_num와 end_num가 주어질 때, 
// start_num부터 end_num까지의 숫자를 차례로 담은 리스트를 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int* solution(int start_num, int end_num) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * (end_num - start_num + 1));
    
    int pos;
    int index = 0;
    for(pos = start_num; pos <= end_num; pos++){
        answer[index++] = pos;
    }
    
    return answer;
}