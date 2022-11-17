#include "menu.h"
int keyControl() {
	int temp = _getch();
	if (temp == 224) {
		temp = _getch();
		if (temp == 72) {
			return UP;
		}
		else if (temp == 80) {
			return DOWN;
		}
	}
	else if (temp == 32) {
		return SUBMIT;
	}
}

void init() {
	system("mode con cols=100 lines=40 | title 도서 대여"); // 콘솔창 크기 및 제목 설정
}

void titleDraw(char *str) {
	int minwidth = strlen(str) + (WIDTH - strlen(str)) / 2;
	printf("\n\n\n%*s", minwidth, str);
}

int mainMenu() {
	int x = 45;
	int y = 15;
	gotoxy(x - 2, y);
	printf(">  로그인");
	gotoxy(x, y + 1);
	printf("회원가입");
	gotoxy(x, y + 2);
	printf("  종료");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 17) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return y - 15;
		}
		}
	}
}

int secondMenu() {
	int x = 42;
	int y = 15;
	gotoxy(x - 2, y);
	printf("> 나의 대여 상태");
	gotoxy(x, y + 1);
	printf("   도서대여");
	gotoxy(x, y + 2);
	printf("   로그아웃");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 17) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return y - 15;
		}
		}
	}
}

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}


void showBookMenu(User *nowUser) {
	//도서 목록 조회
	BOOK books[MAX_NUM] = { 0 };
	ReadBooks(books);
	while (1) {

		printf("안녕하세요 %s님\n", nowUser->name);
		init();
		titleDraw("< 도서 대여 서비스 메인 >");
		switch (secondMenu(nowUser))
		{
		case 0: //나의 대여정보
			break;
		case 1: //도서 대여
			system("mode con cols=1000 lines=400 | title 도서 대여"); // 콘솔창 크기 및 제목 설정
			drawBooks(books, NULL);
			Sleep(5000);
			break;
		case 2: //로그아웃
			return;
			break;
		default:
			break;
		}
		system("cls");
	}
}

