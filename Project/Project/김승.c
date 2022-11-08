#include <stdio.h>
#include <windows.h>

#define UP 0
#define DOWN 1
#define SUBMIT 2
#define WIDTH 100

int keyControl();
void init();
void titleDraw();
int mainMenu();
int secondMenu();
void gotoxy(int, int);

int main() {
	init();
	while (1) {
		titleDraw();
		int menuCode = mainMenu();
		if (menuCode == 0) {

		}
		else if (menuCode == 1) {

		}
		else if (menuCode == 2) {

		}
		system("cls");
	}
	return 0;
}

int keyControl() {
	int temp = getch();
	if (temp == 224) {
		temp = getch();
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
	system("mode con cols=100 lines=40 | title 도서 대여");
}

void titleDraw() {
	char str1[] = "<도서 대여>";
	int minwidth = strlen(str1) + (WIDTH - strlen(str1)) / 2;
	printf("\n\n\n%*s", minwidth, str1);
}

int mainMenu() {
	int x = 45;
	int y = 15;
	gotoxy(45 - 2, 15);
	printf(">  로그인");
	gotoxy(45, 17);
	printf("회원가입");
	gotoxy(45, 19);
	printf(" 종료");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y = y - 2);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 19) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y = y + 2);
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
	int x = 43;
	int y = 15;
	gotoxy(43 - 2, 15);
	printf("> 나의 대여 상태");
	gotoxy(43, 17);
	printf("  도서대여");
	gotoxy(43, 19);
	printf("  로그아웃");
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 15) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y = y - 2);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 19) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, y = y + 2);
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