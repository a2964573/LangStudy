#include <stdio.h>
#include <string.h>

#define TRUE                 1
#define FALSE                0

#define SERVICE_SCORE_INPUT  1
#define SERVICE_SCORE_OUTPUT 2
#define SERVICE_RANK_OUTPUT  3

#define TERM_FIRST           1
#define TERM_SECOND          2

#define SUBJECT_KOREAN       1
#define SUBJECT_ENGLISH      2
#define SUBJECT_MATH         3

typedef struct _INFO {
    char         name     [32];
    char         subject  [32];
    unsigned int score;
    unsigned int term;
} INFO;

int input_score_func(INFO* outInfo)
{
    char         name     [32];
    char         subject  [32];
    unsigned int score     = 0;
    unsigned int term      = 0;
    int          sub_flag  = 0;
    int          len       = 0;

    while(TRUE) {
        printf("학기를 입력하세요\n");
        printf("1: 1학기, 2: 2학기\n\n");
        scanf("%d", &term);
        printf("\n");

        if(term < 1 && term > 2) {
            printf("잘못된 값을 입력하였습니다.\n\n");
            continue;
        }

        printf("%d학기 성적을 입력합니다..\n", term);
        printf("이름을 입력하세요.\n\n");
        scanf("%s", &name);
        printf("\n");

        len = strlen(name);
        name[len] = 0x00;

        printf("입력한 이름은 \'%s\'입니다.\n\n", name);

        printf("과목을 입력해주세요.\n");
        printf("1: 국어, 2: 영어, 3: 수학\n\n");
        scanf("%d", &sub_flag);
        printf("\n");

        switch(sub_flag) {
            case SUBJECT_KOREAN :
                len = sprintf(subject, "국어");
            break;
            case SUBJECT_ENGLISH:
                len = sprintf(subject, "영어");
            break;
            case SUBJECT_MATH   :
                len = sprintf(subject, "수학");
            break;
            default:
                len = 0;
            break;
        }

        subject[len] = 0x00;

        if(subject[0] == 0x00) {
            printf("잘못된 값을 입력하였습니다.\n\n");
            continue;
        }

        printf("%s 점수를 입력해주세요.\n", subject);
        printf("0 ~ 100\n\n");
        scanf("%d", &score);
        printf("\n");

        if(score < 0 || score > 100) {
            printf("잘못된 값을 입력하였습니다.\n\n");
            continue;
        }

        printf("%d학기 %s님의 %s과목 성적은 %d점 입니다.\n\n"
            , term, name, subject, score);

        break;
    }

    strcpy(outInfo->name,    name);
    strcpy(outInfo->subject, subject);
    outInfo->score = score;
    outInfo->term  = term;

    return 0;
}

void main(int argc, char** argv)
{
    char mode_name[64] = {0,}; // 1: 성적입력, 2: 성적출력, 3: 랭킹출력
    int  mode          = 0;    // 1: 성적입력, 2: 성적출력, 3: 랭킹출력
    int  term          = 0;    // 1: 1학기, 2: 2학기
    int  rtn           = 0;

    printf("#############################\n");
    printf("#                           #\n");
    printf("#  성적관리 프로그램입니다  #\n");
    printf("#                           #\n");
    printf("#############################\n\n");

    while(TRUE) {
        printf("실행할 서비스를 입력해주세요.\n");
        printf("1: 성적입력, 2: 성적출력, 3: 랭킹출력\n\n");
        scanf("%d", &mode);
        printf("\n");

        switch(mode) {
            case SERVICE_SCORE_INPUT :
                strcpy(mode_name, "성적입력");
            break;
            case SERVICE_SCORE_OUTPUT:
                strcpy(mode_name, "성적출력");
            break;
            case SERVICE_RANK_OUTPUT :
                strcpy(mode_name, "랭킹출력");
            break;
            default:
                mode_name[0] = 0x00;
            break;
        }

        if(mode_name[0] == 0x00) {
            printf("잘못된 서비스를 입력하였습니다.\n");
            printf("다시 입력해주세요.\n\n");
            continue;
        }

        printf("%s서비스를 시작합니다.\n\n", mode_name);
        break;
    }

    INFO info;
    memset(&info, 0, sizeof(INFO));

    switch(mode) {
        case SERVICE_SCORE_INPUT :
            rtn = input_score_func(&info);
            if(rtn == 0) {
                printf("> info->name    [%s]\n", info.name);
                printf("> info->subject [%s]\n", info.subject);
                printf("> info->score   [%d]\n", info.score);
                printf("> info->term    [%d]\n", info.term);
            }
        break;
        case SERVICE_SCORE_OUTPUT:
        break;
        case SERVICE_RANK_OUTPUT :
        break;
    }

    return;
}