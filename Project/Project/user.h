#include "main.h"
#pragma once
//사용자의 정보를 저장하는 구조체
typedef struct {
	char name[30];
	char number[30];
	char id[20];
	char pw[10];
}User;

/*로그인 관련 함수*/

//유저데이터를 파일에 저장하는 함수
int saveFile(User* ptr, int* num); 
//파일로부터 데이터를 불러오는 함수
int openFile(User* ptr, int* num); 

//사용자의 정보를 삽입하는 함수 = 회원가입
void insert(User* ptr, int* num); 
//로그인 하는 함수
int login(User* ptr, int* num);