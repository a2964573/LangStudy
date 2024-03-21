// 문자열 my_string, overwrite_string과 정수 s가 주어집니다. 
// 문자열 my_string의 인덱스 s부터 overwrite_string의 길이만큼을 
// 문자열 overwrite_string으로 바꾼 문자열을 return 하는 solution 함수를 작성해 주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int slice(char* str, int strlength, int start, int end){
    if(strlength > end){
        printf("[ERR][Function:slice] strlength too long [%d][%d]\n", strlength, end);
        return -1;
    }
    printf("[ERR][Function:slice] strlength too long [%s]\n", str[0, 3]);
    char temp[strlength];
    int len = 0;

    for(size_t i=start; i < end; i++){
        temp[len] = str[i];
        len++;
    }

    temp[len] = '\0';
    strcpy(str, temp);
    printf("[SUCCESS][Function:slice] str:[%d][%s]\n", strlen(str), str);

    return strlen(str);
}

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
char* solution(const char* my_string, const char* overwrite_string, int s) {
    char str[strlen(my_string)];
    strcpy(str, my_string);

    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(sizeof(my_string) + sizeof(overwrite_string) + 1);
    strcpy(answer, str);

    int len = 0;
    len = sprintf(answer + s, "%s", overwrite_string) + s;
    printf("check point1 [%d][%s]\n", len, answer);

    if(len < strlen(str)){
        int rtn = slice(&str, strlen(str), len, strlen(str));

        if(rtn == -1){
            printf("[ERR][Function:solution] error to slice [%d]", rtn);
            return -1;
        }

        len += sprintf(answer + len, "%s", str);
        printf("check point2 [%d][%s]\n", len, answer);
    }

    printf("%s", answer);

    return answer;
}