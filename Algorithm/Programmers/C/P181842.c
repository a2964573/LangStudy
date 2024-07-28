// 어떤 문자열 A가 다른 문자열 B안에 속하면 A를 B의 부분 문자열이라고 합니다. 
// 예를 들어 문자열 "abc"는 문자열 "aabcc"의 부분 문자열입니다.
// 문자열 str1과 str2가 주어질 때, str1이 str2의 부분 문자열이라면 1을 
// 부분 문자열이 아니라면 0을 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* str1, const char* str2) {
    int answer = 0;
    int wLen = 0;
    int cLen = 0;
    int wPos = 0;
    int cPos = 0;

    wLen = strlen(str2);
    cLen = strlen(str1);

    while(wPos < wLen){
        if(str2[wPos] == str1[cPos]){
            cPos++;
            wPos++;
            
            if(cPos == cLen){
                answer = 1;
                break;
            }
        }else{
            if(cPos == 0){
                wPos++;    
            }else{
                cPos = 0;
            }
        }
    }

    return answer;
}