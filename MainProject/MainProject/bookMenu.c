#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

//���� ����ü 
typedef struct book {
	char title[SIZE];
	char publisher[SIZE];
	char author[SIZE];
	int state;
}BOOK;
char state[2][10] = { "���Ⱑ��"," �뿩�� " }; //���� ������ ���¸� ��Ÿ���� ���ڿ� 
char bar[216] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
//������ �˻��Ͽ� �˻������ �����ϴ� �Լ� 
void findBooks(BOOK *books, int type, char *keyword,int *returnList,int *length);
//���������͸� �ҷ����� �Լ�
void ReadBooks(BOOK *books);
//���� �뿩 
void rentBook(BOOK *books,int idx);
//���� ����
void eliminateWord(char *words,char *data);
//ȭ�鿡 ��������� ����ϴ� �Լ�
void drawBooks(BOOK *books,int *list);

//�����Լ�
int main(void) {
	BOOK books[SIZE] = { 0 };
	ReadBooks(books);
	drawBooks(books,NULL);
	char keyword[SIZE];
	while (strcmp(keyword, "")) {
		printf("���� �˻� : ");
		scanf("%s", &keyword);
		int returnList[SIZE] = { 0 };
		int length = 0;
		findBooks(books, 3, keyword, returnList,&length); //���հ˻����� ����
		system("cls");
		printf("%s �˻����\n", keyword);
		drawBooks(books, returnList); //ȭ�鿡 �˻� ����� ���
		if (length > 0) {
			printf("1. �����˻�\n2.���� �뿩\n");
			int menu = 0;
			scanf("%d", &menu);
			if (menu == 2) {
				printf("� ������ �뿩�Ͻðڽ��ϱ�? : ");
				scanf("%d", &menu);
				int wantIdx = *(returnList + (menu - 1))-1;
				if((books+wantIdx)->state== 0) rentBook(books, wantIdx); //�뿩�� ������ ������ ���
				else printf("�ش� ������ ���� �뿩�� �Դϴ�. \n");
			}
		}
		else printf("�˻������ �����ϴ�.\n");
	}
	return 0;
}


void findBooks(BOOK *books, int type, char *keyword,int *returnList,int *length) {
	int idx = 0;
	for (int i = 0; strcmp((books + i)->title, ""); i++) {
		switch (type) {
		case 0: //���������� �˻�
			if (strstr((books + i)->title, keyword) != NULL) *(returnList+idx++)= i+1;
			break;
		case 1://���ǻ������ �˻�
			if (strstr((books + i)->publisher, keyword) != NULL) *(returnList + idx++) = i+1;
			break;
		case 2:// ���ڸ����� �˻�
			if (strstr((books + i)->author, keyword) != NULL)*(returnList + idx++) = i+1;
			break;
		case 3: //���հ˻�
			if (strstr((books + i)->author, keyword) != NULL || strstr((books + i)->publisher, keyword) != NULL || strstr((books + i)->title, keyword) != NULL)*(returnList + idx++) = i + 1;
		default:
			break;
		}
	}
	*length = idx; //�˻� ����� ���̸� ���� 
}
void ReadBooks(BOOK *books) {
	FILE *fp;
	char tmp[SIZE * 3] = { 0 };
	char *token = 0;
	int idx = 0, tmpIdx = 0;
	if ((fp = fopen("./books.txt", "r")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	while (!feof(fp)) {
		tmpIdx = 0;
		fgets(tmp, SIZE * 3, fp);
		if (strcmp("��ǰ��\t���ǻ�/���ۻ�\t����/��Ƽ��Ʈ\t�뿩����\n", tmp)) //ù���� ����
		{
			token = strtok(tmp, "\t\n"); // //�� ����Ű�� �������� ��ũ����¡ ����
			while (token != NULL) {
				switch (tmpIdx) {
				case 0: //ù��° ���� ������
					strcpy((books + idx)->title, token);
					break;
				case 1: //�ι�° ���� ���ǻ��
					strcpy((books + idx)->publisher, token);
					break;
				case 2: //����° ���� ���ڸ�
					strcpy((books + idx)->author, token);
					break;
				case 3: //������ ���� �������� 
					(books+idx)->state = atoi(token);
					break;
				default:
					break;
				}
				token = strtok(NULL, "\t\n"); //���� �ٿ��� ���� ��ũ����¡ ����
				tmpIdx++; //���� ������ �̵� 
			}
			idx++;
		}
	}
	fclose(fp);
}
void drawBooks(BOOK *books,int *list) {
	printf("%s", bar);
	printf("| %s |%-80s |%-80s|%-30s | %s |\n", "��ȣ", "                                       ������", "                                       ���ڸ�", "            ���ǻ��", "  ����  ");
	printf("%s", bar);
	//�˻������ ���
	if (list != NULL) {
		for (int t = 0; *(list + t) != 0; t++) {
			int i = *(list + t) - 1;
			printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", t + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
			printf("%s", bar);
		}
	}
	//��ü ����Ʈ�� ��� 
	else for (int i = 0; strcmp((books+i)->title,""); i++) {
		printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", i + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
		printf("%s", bar);
	}
}
void rentBook(BOOK *books,int idx) {
	FILE *fp;
	int i=0;
	if ((fp = fopen("./books.txt", "w")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	(books + idx) ->state = 1;
	fprintf(fp, "��ǰ��\t���ǻ�/���ۻ�\t����/��Ƽ��Ʈ\t�뿩����\n");
	while (1) {
		if(!strcmp((books + i)->title, ""))break;
		if(!strcmp((books + i+1)->title, ""))fprintf(fp, "%s\t%s\t%s\t%d", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		else fprintf(fp, "%s\t%s\t%s\t%d\n",(books+i)->title,(books+i)->publisher,(books+i)->author,(books+i)->state);
		i++;
	}
	fclose(fp);
	printf("%s �뿩�� �Ϸ�Ǿ����ϴ�.!\n",(books+idx)->title);
}
void eliminateWord(char *words, char *data) {
	char* ptr = strstr(words, data);  // simple�� �����ϴ� ��ġ�� ã��
	while (ptr != NULL) {
		strncpy(ptr, " ",1);  
		ptr = strstr(ptr+1,data);
	}
}