/*
�޴����� �Լ��� ��Ƶ� ������� �Դϴ�.
*/
#include "main.h"
#include "user.h"
#include "book.h"
#pragma once
//�޴� �̵� ���� �Լ�
#define UP 0
#define DOWN 1
#define SUBMIT 2
#define WIDTH 100
int keyControl();
void init();
void titleDraw(char *str); //���� ȭ�鿡 �׸���
int mainMenu(); // �α��� �޴�
int secondMenu(); // ���θ޴�
void gotoxy(int, int); //��ǥ �̵�
void showBookMenu(User *nowUser); //���� �뿩 ȭ��

//�뿩�� �������
void showBorrowList(User *nowUser,BOOK *books);

 //���� �˻� �� �뿩 ����
void showBookSearch(User *nowUser,BOOK *books);
void showSubBookSearch(User *nowUser,BOOK *books);
void showBookSearchMenu(User *nowUser, BOOK books);
//����
int selectedOption(int x, int y,int min, int max,int type);
