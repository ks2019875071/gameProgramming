#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct trump {
	int order;
	char shape[3];
	int number;
};

void make_card (trump m_card[]);
void display_card(trump m_card[]);
void shuffle_card(trump m_card[]);
int menu_select(void);

int main (void) {
	trump card[52];
	int c;
	
	while ((c=menu_select()) != 2) {
		make_card(card);
		shuffle_card(card); 

		switch(c) {
			case 1 : display_card(card);
				break;
			default : break;
		}
	}
	
	return 0;
}

int menu_select (void) {
	int select;
	
	printf("1. 카드 뽑기 \n");
	printf("2. 프로그램 종료\n\n");
	
	select=getch()-48;
	return select;
}

void make_card (trump m_card[]) {
	int i, j;
	char shape[4][3] = {"♠", "♣", "♥", "◆"};
	for (i=0; i<4; i++) {
		for (j=i*13; j<i*13+13; j++) {
			m_card[j].order= i;
			strcpy(m_card[j].shape, shape[i]);
			m_card[j].number = j%13+1;
			
			switch (m_card[j].number) {
				case 1 : 
				m_card[j].number = 'A';
				break;
				case 11 : 
				m_card[j].number = 'J';
				break;
				case 12 : 
				m_card[j].number = 'Q';
				break;
				case 13 : 
				m_card[j].number = 'K';
				break;
			}
		}
	}
}

void display_card (trump m_card[]) {
	int i, n, count = 0;
	
	printf("몇 개를 뽑습니까?\n\n");
	scanf(" %d", &n);
	
	for (i=0; i<n; i++) { //n개 출력 
		printf("%s", m_card[i].shape);
		
		if (10<m_card[i].number)
			printf("%-2c", m_card[i].number);
		else
			printf("%-2d", m_card[i].number);
		
		count++;
		
		if (i%13+1 == 13) {
			printf("\n");
			count = 0;
		}
	}
	printf("\n\n");
}

void shuffle_card (trump m_card[]) {
	int i, rnd;
	trump temp;
	srand(time(NULL)); //난수 초기화 
	
	for (i=0; i<52; i++) {
		do {
			rnd = rand()%52;
		} while (rnd == i);
		
		temp = m_card[rnd];
		m_card[rnd] = m_card[i];
		m_card[i] = temp;
	}
}

