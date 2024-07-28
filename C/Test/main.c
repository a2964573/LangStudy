#include "main.h"

struct Example {
    char a[32];
    int b;
    char c;
    char d[13];
};

int getObjectSize(TEST_STRUCT* tt)
{
    int answer = 0;

    answer = sizeof(*tt) / sizeof(tt[0]);

    printf("getObjectSize | sizeof tt: %d / sizeof *tt: %d / sizeof tt[0]: %d\n", sizeof(tt), sizeof(*tt), sizeof(tt[0]));

    return answer;
}

void main()
{
    int rtn = 0;
    TEST_STRUCT tt[16];

    memset(tt, 0, sizeof(tt));

    printf("sizeof TEST_STRUCT: %d\n", sizeof(TEST_STRUCT));

    char* a;
    long long* b;

    printf("sizeof a: %d\n", sizeof(a));
    printf("sizeof b: %d\n", sizeof(b));

    rtn = getObjectSize(tt);
    printf("object size: %d\n", rtn);

    printf("Example size: %d / %d\n", sizeof(struct Example), sizeof(long long));

    return;
}