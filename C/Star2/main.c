#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(){
    int height;
    int space;
    int pos;

    printf("input the star pyramid height. ");
    scanf("%d", &height);

    height <<= 1;

    char* buffer = (char*)malloc(height * sizeof(char) + 1);

    for(pos = 1; pos <= height; pos += 2){
        space = (height - pos) / 2;

        memset(buffer, '\0', _msize(buffer));
        memset(&buffer[0], ' ', space);
        memset(&buffer[space], '*', pos);

        printf("%s\n", buffer);
    }

    free(buffer);

    return 0;
}