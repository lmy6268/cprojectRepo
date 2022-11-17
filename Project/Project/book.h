#include "main.h"
#pragma once

//도서 구조체 
typedef struct book {
	char title[MAX_NUM]; //도서명
	char publisher[MAX_NUM]; //출판사명
	char author[MAX_NUM]; //저자명
	int state; //도서상태
}BOOK;

/* 도서 관련 함수 */

 //현재 도서의 상태를 나타내는 문자열 
extern char state[2][10];
extern char bar[216];

//도서를 검색하여 검색목록을 전달하는 함수 
void findBooks(BOOK *books, int type, char *keyword, int *returnList, int *length);
//도서데이터를 불러오는 함수
void ReadBooks(BOOK *books);
//도서 대여 
void rentBook(BOOK *books, int idx);
//문자 제거
void eliminateWord(char *words, char *data);
//화면에 도서목록을 출력하는 함수
void drawBooks(BOOK *books, int *list);
//도서 반납
void returnBook(BOOK *books);