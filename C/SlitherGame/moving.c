#include "main.h"

int saveLog(playerData* pData, int keyCode){
    char temp[POS_X_MAX * POS_Y_MAX];

    strcpy(temp, pData->log);
    pData->log[0] = '0' + (keyCode % 100);
    strcpy(pData->log + 1, temp);

    return 0;
}

int pressKey(playerData* pData, foodData* fData){
    int keyCode = getch();

    switch(keyCode){
        case KEY_LEFT:
            pData->posX <= 1 ? pData->posX = 1 : --pData->posX;
            break;
        case KEY_DOWN:
            pData->posY >= POS_Y_MAX - 2 ? pData->posY = POS_Y_MAX - 2 : ++pData->posY;
            break;
        case KEY_UP:
            pData->posY <= 1 ? pData->posY = 1 : --pData->posY;
            break;
        case KEY_RIGHT:
            pData->posX >= POS_X_MAX - 2 ? pData->posX = POS_X_MAX - 2 : ++pData->posX;
            break;
        case KEY_EXIT:
            return -1;
        default:
            return 0;
    }

    saveLog(pData, keyCode);

    return 0;
}