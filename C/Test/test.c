#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int utilStringBackSpace(char* buffer, int size, int pos)
{   
    if(buffer == NULL) {
        return -1;
    }   
    
    if(size <= 0) {
        size = strlen(buffer);
    }

    if(pos <= 0) {
        return 0;
    }
	else
	if(pos > size) {
		pos = size;
	}

    int apos = 0;
	int bpos;
	for(bpos = 0; bpos < size; bpos++) {
		if(bpos == pos - 1) {
			continue;
		}

		buffer[apos++] = buffer[bpos];
	}
	buffer[apos] = 0x00;


    return apos;
}
int _isValidChar(int ch)
{   
    return (isdigit(ch) ||
            (ch >= '~' && ch <= '/') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z'));
}

int utilGetString(char* buffer, int size)
{   
    if(buffer == NULL || size <= 0) {
        return -1;
    }

/*
    MEVENT event;
    
    int x;
    int y;
*/
    int key = 0;
    int len = sizeof(buffer);
    while(len < size - 1) {
        key = 'k';
/*        
        if(key == KEY_ESC) {
            break;
        }   
        else
        if(key == KEY_BACKSPACE) {
*/
		if(key == 127) {
/*
            getyx(stdscr, y, x);
*/
            utilStringBackSpace(buffer, len, len);
            continue;
        }   
/*
        else
        if(key == KEY_DC) {
            getyx(stdscr, y, x);
            utilStringDelete(buffer, len, x);
            continue;
        }   
        else    
        if(key == KEY_MOUSE) {
            if(getmouse(event) != OK) {
                continue;
            }   
            
            if(event.bstate & BUTTON1_CLICKED) {
                return event.y;
            }
        
            continue;
        }   
*/
        
        if(_isValidChar(key)) {
            len = sprintf(&buffer[len], "%c", key);
        }
    }
	buffer[len] = 0x00;


    return len;
}


int utilStringDelete(char* buffer, int size, int pos)
{       
    if(buffer == NULL) {
        return -1;
    }   
        
    if(size <= 0) {
        size = strlen(buffer);
    }
        
    if(pos > size) {
        return 0;
    }

    int apos = 0;
    int bpos;
    for(bpos = 0; bpos < size; bpos++) {
        if(bpos == pos) {
            continue;
        }

        buffer[apos++] = buffer[bpos];
    }
    buffer[apos] = 0x00;


    return apos;
}

int main() {
	char buffer[1024] = {0,};
	int len = utilGetString(buffer, 1024);
	printf("[%d][%s]", len, buffer);

    return 0;
}

