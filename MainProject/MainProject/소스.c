#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <Windows.h>
#define SIZE 100

typedef struct user {         //유저 회원가입 정보를 구조체로 표현
	char name[SIZE]; // 이름
	char id[SIZE]; // 아이디
	char password[SIZE]; //비밀번호
} USER;

typedef struct book {
	char title[SIZE];
	char publisher[SIZE];
	char author[SIZE];
}BOOK;

void menu();  // 로그인/회원가입 선택메뉴
USER information(FILE* fp); // 사용자로부터 데이터를 받아 구조체로 반환
void sign_up(FILE* fp); //회원가입
int overlap_check(FILE* fp, char*id);   // 아이디 중복확인
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
		fprintf(stderr, "오류");
		exit(1);
	}
	while (1)
	{
		menu();
		printf("\n원하시는 메뉴를 입력해주세요: ");
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
	getchar();   //줄바꿈 문자 제거
	Sleep(1000);
	system("cls");
	printf("안녕하세요! 회원가입을 시작하겠습니다!\n\n");
	printf("이름을 입력해주세요 : ");
	gets(data.name);
	while (1) {
		printf("사용하실 아이디를 입력해주세요 : ");
		gets(data.id);
		if (overlap_check(fp, ))
	}

	printf("사용하실 비밀번호를 입력해주세요 : ");
	gets(data.password);
	return data;
}




void menu()
{
	printf("로그인 - 1\n회원가입 - 2\n종료 - 3\n");
}




void sign_up(FILE* fp)
{
	USER data;
	data = information();						// 사용자로부터 데이터를 받아서 구조체에 저장
	fseek(fp, 0, SEEK_END);					// 파일의 끝으로 간다
	fwrite(&data, sizeof(data), 1, fp);		// 구조체 데이터를 파일에 쓴다
	size = 0;
}





int overlap_check(FILE* fp, char* id)	// 아이디 중복확인
{
	USER data;
	fseek(fp, 0, SEEK_SET);
	getchar(); //줄바꿈 문자 제거
	printf("중복확인\n사용하실 아이디를 입력해주세요 : ");
	gets_s(id, SIZE);
	while (!feof(fp)) {
		fread(&data, sizeof(data), 1, fp);
		if (!strcmp(data.id, id)) {
			printf("이미 있는 아이디입니다.\n");
			return 0;
		}
	}
	printf("사용하실 수 있는 아이디입니다!\n");
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
	printf("아이디를 입력하세요: ");
	gets_s(id, SIZE);
	printf("비밀번호를 입력하세요: ");
	gets_s(password, SIZE);
	while (!feof(fp)) {
		fread(user, sizeof(USER), 1, fp);
		printf("현재 검색 데이터: 아이디- %s 비밀번호 - %s, \n 입력값 : 아이디- %s 비밀번호 - %s \n", user->id, user->password, id, password);
		int idCheck = strcmp(user->id, id);
		int pwCheck = strcmp(user->password, password);
		if (!idCheck && !pwCheck)
		{
			printf("로그인성공\n");
			return 1;
		}
		else if (!idCheck) hasID = 1;
	}
	if (hasID)printf("비밀번호가 일치하지 않습니다. 다시 시도해주세요.\n");
	else printf("일치하는 회원정보가 존재하지 않습니다. 다시 시도해 주세요.\n");
	return 0;
}

void showMainMenu(USER *user) {
	printf("환영합니다 %s님.\n", user->name);
	Sleep(3000);
	system("cls");
}

void ReadBooks(BOOK *books) {
	FILE *fp;
	if ((fp = fopen("userBook.txt", "r")) == NULL) {
		fprintf(stderr, "오류");
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
