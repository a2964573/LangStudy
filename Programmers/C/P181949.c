// 영어 알파벳으로 이루어진 문자열 str이 주어집니다. 
// 각 알파벳을 대문자는 소문자로 소문자는 대문자로 변환해서 출력하는 코드를 작성해 보세요.

#include <stdio.h>
#include <ctype.h>
#define LEN_INPUT 10

int main(void) {
    char s1[LEN_INPUT];
    scanf("%s", s1);

    size_t i = 0;
    while(1){
        if(s1[i] == '\0') break;

        if(s1[i] >= 65 && s1[i] <= 90){
            s1[i] = tolower(s1[i]);
        }else{
            s1[i] = toupper(s1[i]);
        } 

        i++;
    }

    printf("%s", s1);

    return 0;
}