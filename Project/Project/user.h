#pragma once
#include "main.h"
#include "structs.h"



/*�α��� ���� �Լ�*/

//���������͸� ���Ͽ� �����ϴ� �Լ�
int saveFile(User* ptr, int* num); 
//���Ϸκ��� �����͸� �ҷ����� �Լ�
int openFile(User* ptr, int* num); 

//������� ������ �����ϴ� �Լ� = ȸ������
void insert(User* ptr, int* num); 
//�α��� �ϴ� �Լ�
int login(User* ptr, int* num);