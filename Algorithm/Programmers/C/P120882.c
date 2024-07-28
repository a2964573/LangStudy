// 영어 점수와 수학 점수의 평균 점수를 기준으로 학생들의 등수를 매기려고 합니다. 
// 영어 점수와 수학 점수를 담은 2차원 정수 배열 score가 주어질 때, 
// 영어 점수와 수학 점수의 평균을 기준으로 매긴 등수를 담은 배열을 return하도록 solution 함수를 완성해주세요.

#include <stdio.h>

// score_rows는 2차원 배열 score의 행 길이, score_cols는 2차원 배열 score의 열 길이입니다.
int* solution(int** score, size_t score_rows, size_t score_cols)
{
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int) * score_rows);
    memset(answer, 0x00, sizeof(int) * score_rows);

    int sumA;
    int sumB;
    int aPos;
    int bPos;
    for(aPos = 0; aPos < score_rows; aPos++){
        answer[aPos]++;
        sumA = score[aPos][0] + score[aPos][1];

        for(bPos = 0; bPos < score_rows; bPos++){
            if(aPos == bPos){
                continue;
            }

            sumB = score[bPos][0] + score[bPos][1];

            if(sumA < sumB){
                answer[aPos]++;
            }
        }
    }

    return answer;
}