#pragma once
#include "main.h"
#include "structs.h"




/* 도서 관련 함수 */

 //현재 도서의 상태를 나타내는 문자열 
extern char state[2][10];
extern char bar[216];

//도서를 검색하여 검색목록을 전달하는 함수 
void findBooks(BOOK *books, int type, char *keyword, int *returnList, int *length);
//도서데이터를 불러오는 함수
void ReadBooks(BOOK *books);
//도서 대여 
void rentBook(BOOK *books, int idx,User *user );
//문자 제거
void eliminateWord(char *words, char *data);
//화면에 도서목록을 출력하는 함수
void drawBooks(BOOK *books, int *list,int size,int type);
//도서 반납
void returnBook(BOOK *books, int idx,User *user);