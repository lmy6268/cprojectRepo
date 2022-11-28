#pragma once
//도서 구조체 
typedef struct book {
	char title[MAX_NUM]; //도서명
	char publisher[MAX_NUM]; //출판사명
	char author[MAX_NUM]; //저자명
	int state; //도서상태
}BOOK;
//사용자의 정보를 저장하는 구조체
typedef struct {
	int orderNum; //순서 번호
	char name[30]; //사용자명
	char number[30]; //사용자 휴대폰 번호
	char id[20]; //사용자 아이디
	char pw[10]; //사용자 비밀번호
	int books[3]; //사용자 대여 도서
}User;

