#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

#define DIGIT_1       1
#define DIGIT_10      10
#define DIGIT_100     100
#define DIGIT_1000    1000
#define DIGIT_10000   10000
#define DIGIT_100000  100000
#define DIGIT_1000000 1000000

typedef struct {
    int s_num;
    int e_num;
    int c_num;
    int max_calc;
    int cols;
    int rows;
    int digit;
} SETTING;

void init(int argc, char *argv[], SETTING& setting);
int validateSettings(SETTING& setting);
int getDigit(int number);
int multiply(int a, int b, int digit, int len, char* output);

#endif // MAIN_H
