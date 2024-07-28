#include "main.h"

int createFood(playerData* pData, foodData* fData){
    srand(time(NULL));

    int tempX, tempY;
    
    while(1){
        tempX = (rand() % (POS_X_MAX - 3)) + 1;
        if(tempX == pData->posX) continue;
        fData->posX = tempX;

        tempY = (rand() % (POS_Y_MAX - 3)) + 1;
        if(tempY == pData->posY) continue;
        fData->posY = tempY;

        break;
    }

    return 0;
}

int eatFood(playerData* pData, foodData* fData){
    ++pData->score;
    
    fData->posX = -1;
    fData->posY = -1;
    
    return 0;
}

int createTail(playerData* pData, int index){
    int mapIndex, headIndex, baseIndex;

    headIndex = (POS_X_MAX + 1) * pData->posY + pData->posX;
    baseIndex = index == 0 ? headIndex : pData->lastTailIdx;

    switch(pData->log[index]){
        case '4':
            mapIndex = baseIndex + 1;
            break;
        case '6':
            mapIndex = baseIndex - (POS_X_MAX + 1);
            break;
        case '7':
            mapIndex = baseIndex + POS_X_MAX + 1;
            break;
        case '8':
            mapIndex = baseIndex - 1;
            break;
    }

    if(mapIndex == headIndex){
        pData->lastTailIdx = mapIndex;

        return 0;
    }

    return mapIndex;
}

int render(playerData* pData, foodData* fData){
    char map[POS_X_MAX * POS_Y_MAX * 3 + 1];

    if(pData->posX == fData->posX && pData->posY == fData->posY){
        eatFood(pData, fData);
    }
    
    if(fData->posX == -1 && fData->posY == -1){
        createFood(pData, fData);
    }

    printf("Scroe: %d\n", pData->score);

    for(size_t i = 0; i < POS_Y_MAX; i++){
        for(size_t j = 0; j < POS_X_MAX; j++){
            if(i == 0 || i == POS_Y_MAX - 1){
                strcat(map, ".");
            }else if(j == 0 || j == POS_X_MAX - 1){
                strcat(map, ".");
            }else if(i == pData->posY && j == pData->posX){
                strcat(map, "O");
            }else if(i == fData->posY && j == fData->posX){
                strcat(map, "*");
            }else{
                strcat(map, " ");
            }
        }
        strcat(map, "\n");
    }

    for(size_t i = 0; i < pData->score; i++){
        int rtn = createTail(pData, i);

        if     (rtn ==  0) continue;
        else if(rtn == -1) break;

        pData->lastTailIdx = rtn;
        map[pData->lastTailIdx] = 'o';
    }

    printf("%s", map);
    
    return 0;
}