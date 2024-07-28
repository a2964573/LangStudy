#include "main.h"

int main() {
    system("cls");

    playerData pData;
    foodData fData;

    pData.posX          = POS_X_MAX/2;
    pData.posY          = POS_Y_MAX/2;
    pData.score         = 0;
    pData.lastTailIdx   = -1;
    pData.log[0]        = '\0';

    fData.posX          = -1;
    fData.posY          = -1;

    while(1){
        render(&pData, &fData);
        int rtn = pressKey(&pData, &fData);
        
        system("cls");
        
        if(rtn == -1){
            return 0;
        }
    }

    return 0;
}