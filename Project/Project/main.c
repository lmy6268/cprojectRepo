#include "main.h"
#include "user.h"
#include "menu.h"
//메인함수
int main() {
	User user[MAX_NUM]; //사용자 정보를 저장할 구조체 배열
	int person = 0; //저장된 user수
	openFile(user, &person);//저장된 데이터를 불러오는 함수
	init(); //화면 크기 초기화
	while (1) {
		titleDraw("<도서 대여 프로그램>");
		switch (mainMenu())
		{
		case 0: //로그인
			system("cls");
			gotoxy(0, 0);
			int result = login(user, &person);
			if (result != -1) {
				system("cls");
				User *nowUser = user + result;
				showBookMenu(nowUser);
			}
			else Sleep(500);
			break;
		case 1: //회원가입
			gotoxy(0, 0);
			system("cls");
			insert(user, &person);
			saveFile(user, &person);
			break;
		default:
			return 0;
		}
		system("cls");
	}
}