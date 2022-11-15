#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <Windows.h>
#define SIZE 100

typedef struct user {         //���� ȸ������ ������ ����ü�� ǥ��
	char name[SIZE]; // �̸�
	char id[SIZE]; // ���̵�
	char password[SIZE]; //��й�ȣ
} USER;

typedef struct book {
	char title[SIZE];
	char publisher[SIZE];
	char author[SIZE];
}BOOK;

void menu();  // �α���/ȸ������ ���ø޴�
USER information(FILE* fp); // ����ڷκ��� �����͸� �޾� ����ü�� ��ȯ
void sign_up(FILE* fp); //ȸ������
int overlap_check(FILE* fp, char*id);   // ���̵� �ߺ�Ȯ��
int login(FILE* fp);
void showMainMenu(USER *user);
void ReadBooks(BOOK *books);

int size = 0;

int main(void)
{
	FILE* fp;
	USER mainUser;
	int select;
	if ((fp = fopen("userinformation.txt", "a+")) == NULL)
	{
		fprintf(stderr, "����");
		exit(1);
	}
	while (1)
	{
		menu();
		printf("\n���Ͻô� �޴��� �Է����ּ���: ");
		scanf("%d", &select);
		switch (select)
		{
		case 1: if (login(fp, &mainUser)) showMainMenu(&mainUser);
			break;
		case 2: sign_up(fp);
			break;
		case 3: return 0;
		}
	}
	fclose(fp);
	return 0;
}



USER information()
{
	USER  data;
	getchar();   //�ٹٲ� ���� ����
	Sleep(1000);
	system("cls");
	printf("�ȳ��ϼ���! ȸ�������� �����ϰڽ��ϴ�!\n\n");
	printf("�̸��� �Է����ּ��� : ");
	gets(data.name);
	while (1) {
		printf("����Ͻ� ���̵� �Է����ּ��� : ");
		gets(data.id);
		if (overlap_check(fp, ))
	}

	printf("����Ͻ� ��й�ȣ�� �Է����ּ��� : ");
	gets(data.password);
	return data;
}




void menu()
{
	printf("�α��� - 1\nȸ������ - 2\n���� - 3\n");
}




void sign_up(FILE* fp)
{
	USER data;
	data = information();						// ����ڷκ��� �����͸� �޾Ƽ� ����ü�� ����
	fseek(fp, 0, SEEK_END);					// ������ ������ ����
	fwrite(&data, sizeof(data), 1, fp);		// ����ü �����͸� ���Ͽ� ����
	size = 0;
}





int overlap_check(FILE* fp, char* id)	// ���̵� �ߺ�Ȯ��
{
	USER data;
	fseek(fp, 0, SEEK_SET);
	getchar(); //�ٹٲ� ���� ����
	printf("�ߺ�Ȯ��\n����Ͻ� ���̵� �Է����ּ��� : ");
	gets_s(id, SIZE);
	while (!feof(fp)) {
		fread(&data, sizeof(data), 1, fp);
		if (!strcmp(data.id, id)) {
			printf("�̹� �ִ� ���̵��Դϴ�.\n");
			return 0;
		}
	}
	printf("����Ͻ� �� �ִ� ���̵��Դϴ�!\n");
	return 1;
}




int login(FILE* fp, USER *user)
{
	char id[SIZE];
	char password[SIZE];
	int hasID = 0;
	Sleep(1000);
	system("cls");
	fseek(fp, 0, SEEK_SET);
	getchar();
	printf("���̵� �Է��ϼ���: ");
	gets_s(id, SIZE);
	printf("��й�ȣ�� �Է��ϼ���: ");
	gets_s(password, SIZE);
	while (!feof(fp)) {
		fread(user, sizeof(USER), 1, fp);
		printf("���� �˻� ������: ���̵�- %s ��й�ȣ - %s, \n �Է°� : ���̵�- %s ��й�ȣ - %s \n", user->id, user->password, id, password);
		int idCheck = strcmp(user->id, id);
		int pwCheck = strcmp(user->password, password);
		if (!idCheck && !pwCheck)
		{
			printf("�α��μ���\n");
			return 1;
		}
		else if (!idCheck) hasID = 1;
	}
	if (hasID)printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �õ����ּ���.\n");
	else printf("��ġ�ϴ� ȸ�������� �������� �ʽ��ϴ�. �ٽ� �õ��� �ּ���.\n");
	return 0;
}

void showMainMenu(USER *user) {
	printf("ȯ���մϴ� %s��.\n", user->name);
	Sleep(3000);
	system("cls");
}

void ReadBooks(BOOK *books) {
	FILE *fp;
	if ((fp = fopen("userBook.txt", "r")) == NULL) {
		fprintf(stderr, "����");
		exit(1);
	}
	int idx = 0;
	while (!feof(fp)) {
		int tmpIdx = 0;
		char tmp[SIZE * 4] = { 0 };
		fgets(tmp, SIZE * 4, fp);
		char *token = strtok(tmp, ",");
		strcpy((books + idx)->title, token);
		token = strtok(NULL, ",");
		strcpy((books + idx)->author, token);

	}
}
