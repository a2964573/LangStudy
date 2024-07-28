// main.h
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <cstring>
#include <cstdlib>

typedef struct {
    int  x;
    int  reverse_x;
    int  y;
    int  height;
    int  count;
    int  offset;
    bool mode;
} SETTING;


void init(int& argc, char* argv[], SETTING& setting) noexcept;
int addStr(char* output, int& pos, const std::string str) noexcept;
void printNormalStar(SETTING& setting, int& pos, char* output) noexcept;
void printReverseStar(SETTING& setting, int& pos, char* output) noexcept;

#endif // MAIN_H