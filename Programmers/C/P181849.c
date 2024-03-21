// 한 자리 정수로 이루어진 문자열 num_str이 주어질 때, 
// 각 자리수의 합을 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* num_str) {
    int answer = 0;
    
    int pos;
    for(pos = 0; pos < strlen(num_str); pos++){
        answer += num_str[pos];
    }
    
    answer -= strlen(num_str) * 48;
    
    return answer;
}