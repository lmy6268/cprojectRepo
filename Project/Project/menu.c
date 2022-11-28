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
	system("mode con cols=100 lines=40 | title ���� �뿩"); // �ܼ�â ũ�� �� ���� ����
}

void titleDraw(char *str) {
	int minwidth = strlen(str) + (WIDTH - strlen(str)) / 2;
	printf("\n\n\n%*s", minwidth, str);
}

int mainMenu() {
	int x = 45;
	int y = 15;
	gotoxy(x - 2, y);
	printf(">  �α���");
	gotoxy(x, y + 1);
	printf("ȸ������");
	gotoxy(x, y + 2);
	printf("  ����");
	return selectedOption(x, y, 15, 17, 0);
}

int secondMenu() {
	int x = 42;
	int y = 15;
	gotoxy(x - 2, y);
	printf("> ���� �뿩 ����");
	gotoxy(x, y + 1);
	printf("   �����뿩");
	gotoxy(x, y + 2);
	printf("   �α׾ƿ�");
	return selectedOption(x, y, 15, 17, 0);

}
//�ɼ� ����
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
	//���� ��� ��ȸ
	BOOK books[MAX_NUM] = { 0 };
	ReadBooks(books);
	while (1) {
		init();

		titleDraw("< ���� �뿩 ���� ���� >");
		printf("\n\n %38s�ȳ��ϼ��� %s��\n\n", "", nowUser->name);
		switch (secondMenu(nowUser))
		{
		case 0: //���� �뿩����
			showBorrowList(nowUser, books);
			break;
		case 1: //���� �뿩
			showBookSearch(nowUser, books);
			break;
		case 2: //�α׾ƿ�
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
		system("mode con cols=100 lines=40 | title ���� �뿩 ���"); // �ܼ�â ũ�� �� ���� ����
		printf("< ���� �뿩 ��� > \n");
		printf("���� �뿩���� ������ �����ϴ�. \n");
	}
	else drawBooks(books, nowUser->books, length, 1);
	Sleep(2000);

}
//���� �˻�ȭ��
void showSubBookSearch(User *nowUser, BOOK *books) {
	int x = 2, y = 4;
	char keyword[300];
	int resultBooks[100] = { 0 }, resultLength = 0;
	while (1) {
		memset(resultBooks, 0, 100 * sizeof(int));
		system("cls");
		system("mode con cols=100 lines=40 | title ���� �˻�"); // �ܼ�â ũ�� �� ���� ����
		printf("\t\t\t<���� �˻�>\t\t\t\n\n");
		printf("�˻�� �Է����ּ���: ");
		while (1) {
			scanf("%s", &keyword);
			if (getchar() == '\n') break;
		}
		findBooks(books, 3, keyword, resultBooks, &resultLength);
		int breakFlag = 0;
		while (1) {
			if (breakFlag) break;
			system("cls");
			if (resultLength == 0) printf("�˻������ �����ϴ�. \n");
			else drawBooks(books, resultBooks, resultLength, 0);
			gotoxy(x - 2, y);
			printf(">");
			gotoxy(x, y + (resultLength * 2));
			printf("  1. ���� �˻�\n");
			gotoxy(x, y + (resultLength * 2) + 2);
			printf("  2. ���� �뿩 ȭ������ \n");
			int selected = selectedOption(x, y, y, y + (resultLength * 2) + 2, 1);
			if (selected <= resultLength) {
				int length = 0;
				for (int i = 0; *((nowUser->books) + i) != -1 && i < 3; i++)length++;
				int idx = *(resultBooks + selected - 1) - 1;
				if ((books + idx)->state == 1) {
					system("cls");
					printf("�̹� �뿩 ���� �����Դϴ�.");
					Sleep(1000);
				}
				else if (length == 3) {
					system("cls");
					printf("�뿩 ����� ���� á���ϴ�. �ݳ� �� �̿��� �ּ���.");
					Sleep(1000);
				}
				else while (1) {
					system("cls");
					system("mode con cols=100 lines=40 | title ���� �˻�"); // �ܼ�â ũ�� �� ���� ����
					printf("\n%s ������ �뿩�Ͻðڽ��ϱ�? ", (books + idx)->title);
					gotoxy(x - 2, y+1);
					printf(">");
					gotoxy(x, y + 1);
					printf("  1. �� \n");
					gotoxy(x, y + 2);
					printf("  2. �ƴϿ� \n");
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
			case 1: //�˻�ȭ������
				breakFlag = 1;
				break;
			case 2: //��������
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
		drawBooks(books, NULL, bookLength, NULL); //ȭ�鿡 ���� ����� ��� 
		gotoxy(x - 2, y);
		printf(">");
		gotoxy(x, y + (bookLength * 2));
		printf("  1. ���� �˻�\n");
		gotoxy(x, y + (bookLength * 2) + 2);
		printf("  2. ���� ȭ������ \n");
		int selected = selectedOption(x, y, y, y + (bookLength * 2) + 2, 1);
		gotoxy(x - 2, y + (bookLength * 2) + 5);
		if (selected <= bookLength) {
			printf("%s", (books + selected - 1)->title);
		}
		else {
			if (selected - bookLength == 1) {
				showSubBookSearch(nowUser, books);
			}
			else return; //���� ȭ������
		}
		system("cls");
	}

}
