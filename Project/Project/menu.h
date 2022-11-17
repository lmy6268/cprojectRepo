/*
메뉴관련 함수를 모아둔 헤더파일 입니다.
*/
#include "main.h"
#include "user.h"
#include "book.h"
#pragma once
//메뉴 이동 관련 함수
#define UP 0
#define DOWN 1
#define SUBMIT 2
#define WIDTH 100
int keyControl();
void init();
void titleDraw(char *str); //제목 화면에 그리기
int mainMenu(); // 로그인 메뉴
int secondMenu(); // 메인메뉴
void gotoxy(int, int); //좌표 이동
void showBookMenu(User *nowUser); //도서 대여 화면