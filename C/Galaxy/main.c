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

BOOL IsKeyDown(int Key)
{
	return ((GetAsyncKeyState(Key) & 0x8000) != 0);
	// GetAsyncKeyState : 현재 무슨 키가 입력되는지 확인
	// 0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
}







int main()
{
	CONSOLE_CURSOR_INFO cursorInfo; //커서깜빡임제거
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	system("chcp 65001"); //gcc 한글 깨짐
	player.x = UX;
	player.y = UY;
	player.hp = 3;

	for (int i = 0; i < MAXENEMY; i++)
		enemy[i].count = 0;
		system("cls");
	for (int count = 0;; count++)
	{
		PrintFloor();
		gotoxy(player.x, player.y);
		printf("<●>");
		if (count % 2 == 0)
		{
			if (IsKeyDown(VK_LEFT))
			{
				if (player.x > BX + 2)
				{
					gotoxy(player.x, player.y);
					printf("    ");
					player.x--;
					gotoxy(player.x, player.y);
					printf("<●>");
				}
			}
			if (IsKeyDown(VK_RIGHT))
			{
				if (player.x < BW - 5)
				{
					gotoxy(player.x, player.y);
					printf("    ");
					player.x++;
					gotoxy(player.x, player.y);
					printf("<●>");
				}
			}
			if (IsKeyDown(VK_UP))
			{
				if (player.y > 2)
				{
					gotoxy(player.x, player.y);
					printf("    ");
					player.y--;
					gotoxy(player.x, player.y);
					printf("<●>");
				}
			}
			if (IsKeyDown(VK_DOWN))
			{
				if (player.y < 25)
				{
					gotoxy(player.x, player.y);
					printf("    ");
					player.y++;
					gotoxy(player.x, player.y);
					printf("<●>");
				}
			}
		}
		if (count % 4 == 0)
		{
			if (IsKeyDown(VK_SPACE))
			{
				CreateBullet();
			}
		}
		if (IsKeyDown(VK_ESCAPE) || player.hp <= 0)
			break;


		if (rand() % 5 == 0)
		{
			CreateEnemy();
		}
		if (count % enemyframe == 0)
		MoveEnemy();
		PlayerHit();
		MoveBullet();
		Enemyfall();
		Sleep(20);
	}
	system("cls");
	gotoxy(UX, UY);
	printf("Game Over");
	gotoxy(UX, UY + 2);
	Sleep(1000);
	getch();
	return 0;
}

void PlayerHit() //플레이어피격
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (enemy[i].exist == FALSE) continue;
		if (enemy[i].y == player.y && abs(enemy[i].x - player.x) <= 0)
		{
			player.hp -= 1;
			if (player.hp <= 0)
				player.hp = 0;
				return;
		}
	}
}

void CreateEnemy() //적군생성
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (enemy[i].exist == FALSE)
		{
			enemy[i].x = rand()% 50 +23;
			enemy[i].y = 1;
			enemy[i].exist = TRUE;
			return;
		}
	}
}	
			
void CreateBullet() //총알
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (pBullet[i].exist == FALSE)
		{
			pBullet[i].x = player.x;
			pBullet[i].y = player.y - 1;
			pBullet[i].exist = TRUE;
			return;
		}
	}
}

void MoveEnemy() //적움직임
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (enemy[i].exist == TRUE)
		{
			gotoxy(enemy[i].x, enemy[i].y);
			printf("  ");
			enemy[i].y +=1;
			gotoxy(enemy[i].x, enemy[i].y);
			puts("★");
		if (enemy[i].y>25)
		{
			gotoxy(enemy[i].x, enemy[i].y);
			enemy[i].exist = FALSE;
			printf("  ");
		}
		}
	}  
}   
    
void Enemyfall() //적제거
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (enemy[i].exist == FALSE)
			continue;
		for (int j = 0; j < MAXBULLET; j++)
		{
			if (enemy[i].y == pBullet[j].y && abs(enemy[i].x - pBullet[j].x) <= 2)
			{
				gotoxy(pBullet[j].x, pBullet[j].y);
				printf("  ");
				enemy[i].exist = FALSE;
				pBullet[j].exist = FALSE;
				gotoxy(enemy[i].x, enemy[i].y);
				printf("     ");
				break;
			}
		}
	}
}

void MoveBullet()  //총알움직임
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		if (pBullet[i].exist == TRUE)
		{
			gotoxy(pBullet[i].x, pBullet[i].y);
			printf("  ");
			pBullet[i].y--;
			gotoxy(pBullet[i].x, pBullet[i].y);
			printf("||");
			if (pBullet[i].y <= 1)
			{
				gotoxy(pBullet[i].x, pBullet[i].y);
				printf("  ");
				pBullet[i].exist = FALSE;
			}
		}
	}
}


void PrintFloor()  //맵 필드
{
	for (int i = BX; i < BW + 1; i++)
	{
		gotoxy(i, 0);
		printf("-");
		gotoxy(i, 27);
		printf("-");

	}

	for (int i = BY; i < BH + 1; i++)
	{
		gotoxy(20, i);
		printf("ㅣ");
		gotoxy(80, i);
		printf("ㅣ");
	}
	//플레이어 HP
	gotoxy(BW + 7, 9);
	printf("Player HP");
	switch (player.hp)
	{
	case 3:
		gotoxy(BW + 7, 10);
		printf("♥ ♥ ♥");
		break;
	case 2:
		gotoxy(BW + 7, 10);
		printf("♥ ♥ ♡");
		break;
	case 1:
		gotoxy(BW + 7, 10);
		printf("♥ ♡ ♡");
		break;
	case 0:
		gotoxy(BW + 7, 10);
		printf("♡ ♡ ♡");
		break;
	}
	gotoxy(BW + 7, 15);
	printf("조작: 방향키");
	gotoxy(BW + 7, 17);
	printf("공격 : SPACE");
}
