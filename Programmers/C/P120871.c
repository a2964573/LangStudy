// 3x 마을 사람들은 3을 저주의 숫자라고 생각하기 때문에 3의 배수와 숫자 3을 사용하지 않습니다. 
// 정수 n이 매개변수로 주어질 때, 
// n을 3x 마을에서 사용하는 숫자로 바꿔 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int find_three(int n)
{
    char number[16] = {0,};
    int len = sprintf(number, "%d", n);

    int pos;
    for(pos = 0; pos < len; pos++){
        if(number[pos] == '3'){
            return 1;
        }
    }

    return 0;
}

int solution(int n) {
    int answer = n;

    int pos;
    for(pos = 1; pos <= answer; pos++){
        if(find_three(pos) == 1){
            answer++;
            continue;
        }

        if(pos % 3 == 0){
            answer++;
            continue;
        }
    }

    return answer;
}