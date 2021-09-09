#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define X_MAX 79 //가로(열)방향의 최대값
#define Y_MAX 24 //세로(행)방향의 최대값

void draw_basic_square(void);

int main(void) {
	draw_basic_square();
	return 0;
}

void draw_basic_square(void) {
	unsigned char a=0xa6, b[7], i;
	for(i=1;i<7;i++)
		b[i]=0xa0+i;
	
	printf("%c%c", a, b[3]);
	printf("%c%c", a, b[4]);
	printf("\n");
	printf("%c%c", a, b[6]);
	printf("%c%c", a, b[5]);
	printf("\n");
}

