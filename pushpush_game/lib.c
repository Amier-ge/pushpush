#include "header.h"

extern unsigned char map[PUSH_SIZE][PUSH_SIZE];

unsigned char game[PUSH_SIZE][PUSH_SIZE];
unsigned char pre_game[PUSH_SIZE][PUSH_SIZE];
int row, column;

int getKey() {

	int key;

	key = getch();
	if(key == 224) key = getch();

	return key;
}

void init() {

	int i, k;

	memset( pre_game, 10, 20*20*sizeof(int) );

	for(i = 0 ; i < PUSH_SIZE ; i++) {

		for(k = 0 ; k < PUSH_SIZE ; k++) {

			//map을 실제 game할 배열에 저장
			game[i][k] = map[i][k];

			//user의 위치정보 저장
			if(game[i][k] == ICON_USER) {
				row = i;
				column = k;
			}
		}
	}

}

void display() {

	int i, k;

	for(i = 0 ; i < PUSH_SIZE ; i++) {
		for(k = 0 ; k < PUSH_SIZE ; k++) { 

			if(game[i][k] != pre_game[i][k]) gotoxy(k*2, i);
			else continue;

			switch(game[i][k]) {

			case ICON_WALL:
				printf("□");
				break;
			
			case ICON_EMPTY:
				printf("  ");
				break;
			
			case ICON_USER:
				printf("ⓦ");
				break;
				
			case ICON_BLOCK:
				printf("☆");
				break;

			case ICON_TARGET:
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 6 );
				printf("★");
				SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), 15 );
				break;
				
			default:
				break;
			}
			pre_game[i][k] = game[i][k]; 
		}
	}

}

int checkMove(int key) {

	int tempRow, tempColumn, temp, move;
	
	tempRow = row;
	tempColumn = column;

	if( (key == KEY_DOWN) || (key == KEY_RIGHT) )	temp = 1;
	else if( (key == KEY_UP) || (key == KEY_LEFT) )	temp = -1;
	else temp = 0;

	move = 1;
	if( (key == KEY_UP) || (key == KEY_DOWN) ) tempRow += temp;
	else if( (key == KEY_RIGHT) || (key == KEY_LEFT) ) tempColumn += temp;

	if(game[tempRow][tempColumn] == ICON_BLOCK) {
		move = 2;
		if( (key == KEY_UP) || (key == KEY_DOWN) ) tempRow += temp;
		else tempColumn += temp;
	}

	if( (game[tempRow][tempColumn] == ICON_EMPTY) || (game[tempRow][tempColumn] == ICON_TARGET) ) {
		return move;
	}

	else {
		return 0;
	}
}

int moveUser(int move, int key) {

	int temp, tempRow, tempColumn;

	tempRow = row;
	tempColumn = column;

	if( (key == KEY_DOWN) || (key == KEY_RIGHT) )	temp = 1;
	else if( (key == KEY_UP) || (key == KEY_LEFT) )	temp = -1;

	if(move == 1) {

		if( (key == KEY_UP) || (key == KEY_DOWN) ) tempRow += temp;
		else if( (key == KEY_RIGHT) || (key == KEY_LEFT) ) tempColumn += temp;

		if(game[tempRow][tempColumn] == ICON_EMPTY) {
			
			game[tempRow][tempColumn] = ICON_USER;

			if(map[row][column] == ICON_USER) game[row][column] = ICON_EMPTY;
			else if(map[row][column] == ICON_TARGET) game[row][column] = ICON_TARGET;
			else game[row][column] = ICON_EMPTY;
		}

		else if(game[tempRow][tempColumn] == ICON_TARGET) {

			game[tempRow][tempColumn] = ICON_USER;

			if(map[row][column] == ICON_EMPTY) game[row][column] = ICON_EMPTY;
			else if(map[row][column] == ICON_TARGET) game[row][column] = ICON_TARGET;
		}
	}

	else if(move == 2) {

		if( (key == KEY_UP) || (key == KEY_DOWN) ) tempRow += temp * 2;
		else if( (key == KEY_RIGHT) || (key == KEY_LEFT) ) tempColumn += temp * 2;

		game[tempRow][tempColumn] = ICON_BLOCK;

		if( (key == KEY_UP) || (key == KEY_DOWN) ) tempRow -= temp;
		else if( (key == KEY_RIGHT) || (key == KEY_LEFT) ) tempColumn -= temp;

		game[tempRow][tempColumn] = ICON_USER;

		if(map[row][column] == ICON_USER) game[row][column] = ICON_EMPTY;
		else if(map[row][column] == ICON_TARGET) game[row][column] = ICON_TARGET;
		else game[row][column] = ICON_EMPTY;
	}

	row = tempRow;
	column = tempColumn;
	
	return 0;
}

int checkFinish() {

	if(game[15][18] == ICON_BLOCK)	{
		if(game[16][17] == ICON_BLOCK) {
			if(game[16][18] == ICON_BLOCK) {
				if(game[17][17] == ICON_BLOCK) {
					if(game[17][18] == ICON_BLOCK) {
						if(game[18][17] == ICON_BLOCK) {
							if(game[18][18] == ICON_BLOCK) return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

void gotoxy(int x, int y) {

	static HANDLE	h = NULL;
	COORD			c = {x, y};

	if(!h) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(h, c);
}