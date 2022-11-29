#include "book.h"

char state[2][10] = { "���Ⱑ��"," �뿩�� " };
char bar[216] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

void findBooks(BOOK *books, int type, char *keyword, int *returnList, int *length) {
	int idx = 0;
	for (int i = 0; strcmp((books + i)->title, ""); i++) {
		switch (type) {
		case 0: //���������� �˻�
			if (strstr((books + i)->title, keyword) != NULL) *(returnList + idx++) = i + 1;
			break;
		case 1://���ǻ������ �˻�
			if (strstr((books + i)->publisher, keyword) != NULL) *(returnList + idx++) = i + 1;
			break;
		case 2:// ���ڸ����� �˻�
			if (strstr((books + i)->author, keyword) != NULL)*(returnList + idx++) = i + 1;
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
	char tmp[MAX_NUM * 3] = { 0 };
	char *token = 0;
	int idx = 0, tmpIdx = 0;
	if ((fp = fopen("books.txt", "r")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	while (!feof(fp)) {
		tmpIdx = 0;
		fgets(tmp, MAX_NUM * 3, fp);
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
					(books + idx)->state = atoi(token);
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

void drawBooks(BOOK *books, int *list, int size,int type) {
	if (list != NULL) {
		if (type == 0) //�˻� ���
		{
			char cmdLine[100];
			sprintf(cmdLine, "mode con cols=250 lines=%d | title ���� �˻� ��� ", (size + 1) * 10);
			system(cmdLine); // �ܼ�â ũ�� �� ���� ����
			printf("< ���� �˻� > \n");
			printf("%s", bar);
			printf("| %s |%-80s |%-80s|%-30s | %s |\n", "��ȣ", "                                       ������", "                                       ���ڸ�", "            ���ǻ��", "  ����  ");
			printf("%s", bar);
			for (int t = 0; *(list + t) != 0; t++) {
				int i = *(list + t) - 1;
				printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", t + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
				printf("%s", bar);
			}
		}
		else if (type == 1) //���� �뿩 ���

		{
			system("mode con cols=250 lines=40 | title ���� �뿩 ���"); // �ܼ�â ũ�� �� ���� ����
			printf("< ���� �뿩 ��� > \n");
			printf("%s", bar);
			printf("| %s |%-80s |%-80s|%-30s | %s |\n", "��ȣ", "                                       ������", "                                       ���ڸ�", "            ���ǻ��", "  ����  ");
			printf("%s", bar);
			for (int t = 0; *(list + t) != 0 && *(list + t) != -1; t++) {
				int i = *(list + t) - 1;
				printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", t + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
				printf("%s", bar);
			}
		}
	}
	//��ü ����Ʈ�� ��� 
	else {
		system("mode con cols=250 lines=400 | title ���� �뿩"); // �ܼ�â ũ�� �� ���� ����
		printf("< ����Ʈ ���� ���� > \n");
		printf("%s", bar);
		printf("| %s |%-80s |%-80s|%-30s | %s |\n", "��ȣ", "                                       ������", "                                       ���ڸ�", "            ���ǻ��", "  ����  ");
		printf("%s", bar);
		for (int i = 0; strcmp((books + i)->title, ""); i++) {
			if (i == size && i != NULL) break;
			printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", i + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
			printf("%s", bar);
		}
	}
}

void rentBook(BOOK *books, int idx, User *user) {
	FILE *fp;
	int i = 0;
	if ((fp = fopen("./books.txt", "w")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	(books + idx)->state = 1;
	fprintf(fp, "��ǰ��\t���ǻ�/���ۻ�\t����/��Ƽ��Ʈ\t�뿩����\n");
	while (1) {
		if (!strcmp((books + i)->title, ""))break;
		if (!strcmp((books + i + 1)->title, ""))fprintf(fp, "%s\t%s\t%s\t%d", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		else fprintf(fp, "%s\t%s\t%s\t%d\n", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		i++;
	}
	fclose(fp);

	if ((fp = fopen("./UserInfo.txt", "w")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	i = 0;
	while (1) {
		if (i >= 3) break;
		else if (*((user->books) + i) == -1)
		{
			*((user->books) + i) = idx + 1; //�뿩�� ������ ����Ʈ�� ����
			break;
		}
		i++;
	}

	//������ ����ڸ� ��� �ľ��ұ�,,, 
	User *users = user - (user->orderNum);
	for (i = 0 ; strcmp((users+i) ->id,""); i++) {
		fprintf(fp, "%d %s %s %s %s ", (users + i)->orderNum,(users + i)->name, (users + i)->number, (users + i)->id, (users + i)->pw);
		for (int j = 0; j < 3; j++) {
			fprintf(fp, "%d, ", *((users + i)->books + j));
		}
		fputc('\n', fp);
	}
	int state = fclose(fp);

	printf("%s �뿩�� �Ϸ�Ǿ����ϴ�.!\n", (books + idx)->title);
}

void returnBook(BOOK *books, int idx, User *user){
	FILE *fp;
	int i = 0;
	if ((fp = fopen("./books.txt", "w")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	(books + idx)->state = 0;
	fprintf(fp, "��ǰ��\t���ǻ�/���ۻ�\t����/��Ƽ��Ʈ\t�뿩����\n");
	while (1) {
		if (!strcmp((books + i)->title, ""))break;
		if (!strcmp((books + i + 1)->title, ""))fprintf(fp, "%s\t%s\t%s\t%d", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		else fprintf(fp, "%s\t%s\t%s\t%d\n", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		i++;
	}
	fclose(fp);

	if ((fp = fopen("./UserInfo.txt", "w")) == NULL) {
		fprintf(fp, "������ ������ϴ�.");
		exit(1);
	}
	int index = -1;
	int tmp = 0;
	for (int i = 0; i < 3; i++) {
		//��ġ ã�� 
		if (*((user->books) + i) == idx + 1) {
			index = i;
			break;
		}
	}
	switch (index)
	{
	case 0:
		tmp = *((user->books));
		*((user->books)) = *((user->books) + 1);
		*((user->books) + 1) = tmp;

		 tmp = *((user->books) + 1);
		 *((user->books)+1) = *((user->books) + 2);
		 *((user->books) + 2) = tmp;

		 *((user->books) + 2) = -1; //���� �����͸� �ű�� �ʱ�ȭ 

		break;
	case 1:
		tmp = *((user->books) + 1);
		*((user->books) + 1) = *((user->books) + 2);
		*((user->books) + 2) = tmp;

		*((user->books) + 2) = -1; //���� �����͸� �ű�� �ʱ�ȭ 
		break;
	default:
		*((user->books) + 2) = -1; 
		break;
	}
	User *users = user - (user->orderNum);
	for (i = 0; strcmp((users + i)->id, ""); i++) {
		fprintf(fp, "%d %s %s %s %s ", (users + i)->orderNum, (users + i)->name, (users + i)->number, (users + i)->id, (users + i)->pw);
		for (int j = 0; j < 3; j++) {
			fprintf(fp, "%d, ", *((users + j)->books + j));
		}
		fputc('\n', fp);
	}
	int state = fclose(fp);

	printf("%s �ݳ��� �Ϸ�Ǿ����ϴ�.!\n", (books + idx)->title);
	Sleep(1000);
}


// ������ ������ �� �ʿ���� ���ڸ� �����ϱ� ����.
void eliminateWord(char *words, char *data) {
	char* ptr = strstr(words, data);  // simple�� �����ϴ� ��ġ�� ã��
	while (ptr != NULL) {
		strncpy(ptr, " ", 1);
		ptr = strstr(ptr + 1, data);
	}
}