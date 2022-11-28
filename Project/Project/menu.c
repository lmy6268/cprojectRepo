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
	return selectedOption(x, y, 15, 17, 0);
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
	return selectedOption(x, y, 15, 17, 0);

}
//옵션 선택
int selectedOption(int x, int y, int min, int max, int type) {
	int originY = y;
	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > min) {
				gotoxy(x - 2, y);
				printf(" ");
				if (type == 0) gotoxy(x - 2, --y);
				else gotoxy(x - 2, y -= 2);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < max) {
				gotoxy(x - 2, y);
				printf(" ");
				if (type == 0)gotoxy(x - 2, ++y);
				else gotoxy(x - 2, y += 2);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			if (type == 0)return y - originY;
			else return y / 2 - originY + 3;
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
		init();

		titleDraw("< 도서 대여 서비스 메인 >");
		printf("\n\n %38s안녕하세요 %s님\n\n", "", nowUser->name);
		switch (secondMenu(nowUser))
		{
		case 0: //나의 대여정보
			showBorrowList(nowUser, books);
			break;
		case 1: //도서 대여
			showBookSearch(nowUser, books);
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
void showBorrowList(User *nowUser, BOOK *books) {
	int x = 2, y = 4, length = 0, idx = 0;
	for (int i = 0; *((nowUser->books) + i) != -1 && i < 3; i++)length++;
	system("cls");
	if (*(nowUser->books) == -1) {
		system("mode con cols=100 lines=40 | title 나의 대여 목록"); // 콘솔창 크기 및 제목 설정
		printf("< 나의 대여 목록 > \n");
		printf("아직 대여중인 도서가 없습니다. \n");
	}
	else drawBooks(books, nowUser->books, length, 1);
	Sleep(2000);

}
//도서 검색화면
void showSubBookSearch(User *nowUser, BOOK *books) {
	int x = 2, y = 4;
	char keyword[300];
	int resultBooks[100] = { 0 }, resultLength = 0;
	while (1) {
		memset(resultBooks, 0, 100 * sizeof(int));
		system("cls");
		system("mode con cols=100 lines=40 | title 도서 검색"); // 콘솔창 크기 및 제목 설정
		printf("\t\t\t<도서 검색>\t\t\t\n\n");
		printf("검색어를 입력해주세요: ");
		while (1) {
			scanf("%s", &keyword);
			if (getchar() == '\n') break;
		}
		findBooks(books, 3, keyword, resultBooks, &resultLength);
		int breakFlag = 0;
		while (1) {
			if (breakFlag) break;
			system("cls");
			if (resultLength == 0) printf("검색결과가 없습니다. \n");
			else drawBooks(books, resultBooks, resultLength, 0);
			gotoxy(x - 2, y);
			printf(">");
			gotoxy(x, y + (resultLength * 2));
			printf("  1. 도서 검색\n");
			gotoxy(x, y + (resultLength * 2) + 2);
			printf("  2. 도서 대여 화면으로 \n");
			int selected = selectedOption(x, y, y, y + (resultLength * 2) + 2, 1);
			if (selected <= resultLength) {
				int length = 0;
				for (int i = 0; *((nowUser->books) + i) != -1 && i < 3; i++)length++;
				int idx = *(resultBooks + selected - 1) - 1;
				if ((books + idx)->state == 1) {
					system("cls");
					printf("이미 대여 중인 도서입니다.");
					Sleep(1000);
				}
				else if (length == 3) {
					system("cls");
					printf("대여 목록이 가득 찼습니다. 반납 후 이용해 주세요.");
					Sleep(1000);
				}
				else while (1) {
					system("cls");
					system("mode con cols=100 lines=40 | title 도서 검색"); // 콘솔창 크기 및 제목 설정
					printf("\n%s 도서를 대여하시겠습니까? ", (books + idx)->title);
					gotoxy(x - 2, y+1);
					printf(">");
					gotoxy(x, y + 1);
					printf("  1. 네 \n");
					gotoxy(x, y + 2);
					printf("  2. 아니오 \n");
					gotoxy(x, y + 1);
					int selected = selectedOption(x, y, y+1, y + 2, 0);
					if (selected == 0) {
						system("cls");
						rentBook(books, idx, nowUser);
						break;
					}
					else break;
				}
			}
			else switch (selected - resultLength)
			{
			case 1: //검색화면으로
				breakFlag = 1;
				break;
			case 2: //메인으로
				return;
			default:
				break;
			}
		}
	}
}

void showBookSearch(User *nowUser, BOOK *books) {
	int x = 2, y = 4, bookLength = 10;
	while (1) {
		drawBooks(books, NULL, bookLength, NULL); //화면에 도서 목록을 띄움 
		gotoxy(x - 2, y);
		printf(">");
		gotoxy(x, y + (bookLength * 2));
		printf("  1. 도서 검색\n");
		gotoxy(x, y + (bookLength * 2) + 2);
		printf("  2. 메인 화면으로 \n");
		int selected = selectedOption(x, y, y, y + (bookLength * 2) + 2, 1);
		gotoxy(x - 2, y + (bookLength * 2) + 5);
		if (selected <= bookLength) {
			printf("%s", (books + selected - 1)->title);
		}
		else {
			if (selected - bookLength == 1) {
				showSubBookSearch(nowUser, books);
			}
			else return; //메인 화면으로
		}
		system("cls");
	}

}
