#pragma once
#include "main.h"
#include "structs.h"




/* ���� ���� �Լ� */

 //���� ������ ���¸� ��Ÿ���� ���ڿ� 
extern char state[2][10];
extern char bar[216];

//������ �˻��Ͽ� �˻������ �����ϴ� �Լ� 
void findBooks(BOOK *books, int type, char *keyword, int *returnList, int *length);
//���������͸� �ҷ����� �Լ�
void ReadBooks(BOOK *books);
//���� �뿩 
void rentBook(BOOK *books, int idx,User *user );
//���� ����
void eliminateWord(char *words, char *data);
//ȭ�鿡 ��������� ����ϴ� �Լ�
void drawBooks(BOOK *books, int *list,int size,int type);
//���� �ݳ�
void returnBook(BOOK *books, int idx,User *user);