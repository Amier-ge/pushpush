#include "header.h"

int main() {

	int key, move;

	//Ŀ�� ���߱�
	CONSOLE_CURSOR_INFO CurInfo;

	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo );

	//�ܼ��� ũ�� ����
	system("mode con: cons = 50 lines = 25");
	
	init();
	system("cls");
	display();

	while(1) {

		key = getKey();
		move = checkMove(key);

		if(move) {
			moveUser(move, key);
			display();

			if( checkFinish() ) break;
		}
	}

	return 0;
}