#pragma once
//���� ����ü 
typedef struct book {
	char title[MAX_NUM]; //������
	char publisher[MAX_NUM]; //���ǻ��
	char author[MAX_NUM]; //���ڸ�
	int state; //��������
}BOOK;
//������� ������ �����ϴ� ����ü
typedef struct {
	int orderNum; //���� ��ȣ
	char name[30]; //����ڸ�
	char number[30]; //����� �޴��� ��ȣ
	char id[20]; //����� ���̵�
	char pw[10]; //����� ��й�ȣ
	int books[3]; //����� �뿩 ����
}User;

