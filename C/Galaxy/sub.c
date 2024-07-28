#include <stdio.h>
#include <conio.h> //키보드입력
#include <windows.h>
#include <stdbool.h> //논리형
#include "main.h"



void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}