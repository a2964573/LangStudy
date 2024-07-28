// 문자열 my_string과 정수 n이 매개변수로 주어질 때, 
// my_string의 앞의 n글자로 이루어진 문자열을 return 하는 solution 함수를 작성해 주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
char* solution(const char* my_string, int n) {
    char* answer = malloc(sizeof(char) * strlen(my_string) + 1);
    
    strcpy(answer, my_string);
    answer[n] = '\0';
    
    return answer;
}