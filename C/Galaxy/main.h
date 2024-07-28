#define BX 20 
#define BY 1  
#define BW 80 // 게임판의 넓이
#define BH 26 // 게임판의 높이
#define UX 50 // 플레이어 초기 위치
#define UY 24 // 플레이어 초기 위치
#define MAXBULLET 8
#define MAXENEMY 10

struct player
{
	int x;
	int y;
	int hp;
	BOOL exist;
} player;

struct bullet
{
	int x;
	int y;
	BOOL exist;
} pBullet[MAXBULLET];

struct Enemy
{
	int x, y;
	int count;
	BOOL exist;
} enemy[MAXENEMY];

void PlayerHit();
void CreateEnemy();
void CreateBullet();
void PrintFloor();
void MoveEnemy();
void MoveBullet();
void Enemyfall();
void removeCursor();

int enemyframe = 7;

void gotoxy(int x, int y);
