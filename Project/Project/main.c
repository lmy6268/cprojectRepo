#include "main.h"
#include "user.h"
#include "menu.h"
//메인함수
int main() {
	User user[MAX_NUM] = { 0 };//사용자 정보를 저장할 구조체 배열

	int person = 0; //저장된 user수
	openFile(user, &person);//저장된 데이터를 불러오는 함수
	init(); //화면 크기 초기화
	while (1) {
		titleDraw("<도서 대여 프로그램>");
		switch (mainMenu())
		{
		case 0: //로그인
			system("cls");
			system("mode con cols=100 lines=40 | title 로그인"); // 콘솔창 크기 및 제목 설정
			gotoxy(0, 0);
			int result = login(user, &person);
			if (result != -1) {
				system("cls");
				User *nowUser = user + result; //현재 사용자 
				showBookMenu(nowUser); //현재 사용자를 이용하여 도서 대여 메뉴로 이동
			}
			else Sleep(500); //로그인 실패 시
			break;
		case 1: //회원가입
			system("mode con cols=100 lines=40 | title 회원가입"); // 콘솔창 크기 및 제목 설정
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