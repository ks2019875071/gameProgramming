#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int display_rule(void);
void gotoxy(int x, int y);
void make_treasure(int tx[], int ty[]);
void display_map(int matrix[][10], int tx[], int ty[]);
void basic_map(void);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);
void game_control(int tx[], int ty[], int tn);

//void make_bomb(int tx[], int ty[]);
void display_result (int hp, int count);

int main(void)
{
    int tx[13], ty[13]; //13칸짜리배열 2개 생성 -> 좌표값 최대 10개 가능, 10~12인덱스는 폭탄 
	int tn; 
	int matrix[10][10]={0}; //10*10 맵
    clock_t start, end; //clock 말고 움직인 횟수로 바꾸고 싶다.
    double pst; //경과 시간
    
	srand(time(NULL)); //난수 생성
    
	tn = display_rule(); //규칙 설명
	
	make_treasure(tx, ty); //보물 위치 지정
	//make_bomb(tx, ty);
	
    start=clock(); //시간 재기 시작

	system("cls");
    game_control(tx, ty, tn);
    
    end=clock();
	pst=(double)(end-start)/CLK_TCK;
	gotoxy(1, 16);
	printf("경과 시간 : %.1f 초", pst);
	getch();
	return 0;
}

int display_rule(void)
{
	int tn;
	
	gotoxy(1, 1);
	printf("보물찾기");
	gotoxy(1,3);
	printf("아래의 바둑판 모양의 격자에는 보물이 \n");
	gotoxy(1,4);
	printf("숨겨져 있습니다. \n");
	gotoxy(1,5);
	printf("화살표(↑↓←→)키를 움직여서 찾습니다. \n");
	gotoxy(1,7);
	
	printf("목표 보물 개수를 입력하세요. 최대 10개.\n");
	do {
		scanf("%ld", &tn);
	} while (tn<0 || tn>10);
	gotoxy(1, 9);
	
	basic_map();
	printf("\n아무키나 누르면 시작합니다. \n");
	if (getch() != NULL) return tn;
}

void basic_map(void) {
	int i, j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			printf("■");
		printf("\n");
	}
}

void make_treasure(int tx[], int ty[])
{
	int i, j;
    for(i=0;i<15;i++)
    {
		tx[i]=rand()%11; //아이템의 x좌표 0~10
		ty[i]=rand()%11; //아이의 y좌표 0~10
	
		for (j=0; j<i; j++) {
			if (tx[i] == tx[j] && ty[i] == ty[j])
				i--;
				continue; 
		} //중복 방지
     }
}
/*
void make_bomb(int tx[], int ty[])
{
	int i, j;
    for(i=10;i<13;i++)
    {
		tx[i]=rand()%11; //폭탄의 x좌표 0~10
		ty[i]=rand()%11; //폭탄의 y좌표 0~10
	
		for (j=0; j<i; j++) {
			if (tx[i] == tx[j] && ty[i] == ty[j]) {
				i--;
			}
		} //중복 방지		
     }
}
*/
void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void display_map(int matrix[][11], int tx[], int ty[])
{
	int i, j;
	basic_map();
	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
			if (matrix[i][j]==1)
			{
				gotoxy(2*i-1, j);
				printf("□");
			}
			else if (matrix[i][j]==2)
			{
				gotoxy(2*i-1, j);
				printf("★");
			}	
			else if (matrix[i][j]==3)
			{
				gotoxy(2*i-1, j);
				printf("◎");
			}
}
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:  //위쪽(상) 방향의 화살표 키 입력
		*y1=*y1-1;
		if (*y1<1)	*y1=1; //y좌표의 최소값
		break;
	case 75:  //왼쪽(좌) 방향의 화살표 키 입력
		*x1=*x1-2;            //x좌표의 감소값
		if (*x1<1)	*x1=1; //x좌표의 최소값
		break;
	case 77:  //오른쪽(우) 방향의 화살표 키 입력
		*x1=*x1+2;               //x좌표의 증가값
		if (*x1>x_b)  *x1=x_b; //x좌표의 최대값
		break;
	case 80:  //아래쪽(하) 방향의 화살표 키 입력
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y좌표의 최대값
		break;
	default:
		return;
	}
}

void display_result (int hp, int count) {
	if (hp<1) {
		gotoxy(1, 15);
		printf("실패! 찾은 보물은 %d개 입니다. \n", &count); 
	}
	
	else {
		gotoxy(1, 15);
		printf("모두 찾았습니다. 게임을 종료합니다. \n");
	}
}

void game_control(int tx[], int ty[], int tn)
{
	int hp, move = 0;
	char key;
	int i, j, count;
	int x=1, y=1;
	int matrix[11][11]={0};
	do
	{
		gotoxy(x, y);
		printf("□");
		matrix[(x+1)/2][y]=1;

		for(i=0;i<tn;i++) {
			if (((x+1)/2==tx[i]) && (y==ty[i]))
				matrix[(x+1)/2][y]=2;
		}
		
		for(i=10;i<13;i++) {
			if (((x+1)/2==tx[i]) && (y==ty[i]))
				matrix[(x+1)/2][y]=3;
		}
		
		gotoxy(1, 1);
		display_map(matrix, tx, ty);

		count=0;
		hp=3;
		for(i=1;i<=10;i++)
			for(j=1;j<=10;j++) {
				if (matrix[i][j]==2)
					count=count+1;
				
				else if (matrix[i][j]==3) //폭탄 밟음 
					hp=hp-1;
			}
		
		gotoxy(1,12);
   		printf("찾은 보물(★)의 개수 : %d / %d", count, tn);
		gotoxy(1, 13);
		printf("남은 생명 : %d / 3", hp);
		gotoxy(1, 14);
		printf("걸음수 : %d", move++/2+1);
		if (hp<1) break;
		key=getch();
		move_arrow_key(key, &x, &y, 19, 10);
	}while(count<tn);
	
	display_result(hp, count);
}
