#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <conio.h>

#define MODE_INSERT  105
#define MODE_UPDATE  117
#define MODE_DELETE  100
#define MODE_REFRESH 114
#define MODE_QUIET   113

typedef struct {
    char filename[1024];
} GLOBAL;

int init(int argc, char* argv[], GLOBAL& _global);
void showTitle() noexcept;

#endif // MAIN_H
