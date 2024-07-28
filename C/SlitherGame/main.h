#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <conio.h>
#include <time.h>
#include <windows.h>

#define KEY_LEFT	104
#define KEY_DOWN	106
#define KEY_UP	    107
#define KEY_RIGHT	108
#define KEY_EXIT	113
#define POS_X_MAX   60
#define POS_Y_MAX   30
#define OUTLINE     -1

int pressKey();
int render();

typedef struct _playerData {
    int posX;
    int posY;
    int score;
    int lastTailIdx;
    char log[POS_X_MAX * POS_Y_MAX];
} playerData;

typedef struct _foodData {
    int posX;
    int posY;
} foodData;