// 문자열 my_string과 정수 n이 매개변수로 주어질 때, 
// my_string의 뒤의 n글자로 이루어진 문자열을 return 하는 solution 함수를 작성해 주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
char* solution(const char* my_string, int n) {
    int len = strlen(my_string);
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(sizeof(char) * (n + 1));
    
    int pos;
    int index = 0;
    
    for(pos = len - n; pos <= len; pos++){
        answer[index++] = my_string[pos];
    }
    
    answer[pos] = '\0';
    
    return answer;
}