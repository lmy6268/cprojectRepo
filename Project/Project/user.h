#pragma once
#include "main.h"
#include "structs.h"



/*로그인 관련 함수*/

//유저데이터를 파일에 저장하는 함수
int saveFile(User* ptr, int* num); 
//파일로부터 데이터를 불러오는 함수
int openFile(User* ptr, int* num); 

//사용자의 정보를 삽입하는 함수 = 회원가입
void insert(User* ptr, int* num); 
//로그인 하는 함수
int login(User* ptr, int* num);