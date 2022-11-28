#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//추후 유지보수를 편히 하기위해 100이란 숫자를
//MAX_NUM으로 설정, 100을 200으로 바꾸면
//MAX_NUM은 200이 됨
#define MAX_NUM 100



//사용자의 정보를 저장하는 구조체
typedef struct {
    char name[30];
    char number[30];
    char id[20];
    char pw[10];
}User;



int saveFile(User* ptr, int* num);
int openFile(User* ptr, int* num);
void insert(User* ptr, int* num);
void login(User* ptr, int* num);
void menu();

void menu() {
    int input;
    User user[MAX_NUM]; //사용자 정보를 저장할 구조체 배열
    int person = 0; //저장된 user수



    openFile(user, &person);//저장된 데이터를 불러오는 함수



    //메뉴 선택
    while (1) {
        printf("***** 메뉴 ***** \n");
        printf("1. 회원가입 \n");
        printf("2. 로그인 \n");
        printf("3. 저장하고 종료 \n");

        printf("메뉴를 선택하세요: ");
        scanf("%d", &input);



        if (input == 1) {
            printf("\n[회원가입] \n");
            insert(user, &person);
        }
        else if (input == 2) {
            printf("\n[로그인] \n");
            login(user, &person);
        }
        else if (input == 3) {
            saveFile(user, &person);
            return ;
        }
        else
            printf("\nError! ReTry! \n\n");
    }

    return;

}



//데이터를 파일에 저장하는 함수
int saveFile(User* ptr, int* num) {

    if (*num > 0) {
        int i, state;
        FILE* fp = fopen("UserInfo.txt", "wt");


        /* fopen함수는 오류발생시 NULL을 리턴하므로
        파일 개방 중 오류발생시 프로그램을 종료 */
        if (fp == NULL) {
            printf("File Open Error!\n");
            return 1;
        }



        //구조체 배열에 저장된 데이터를 파일에 저장
        //줄바꿈으로 구분하여 저장
        for (i = 0; i < *num; i++) {
            fprintf(fp, "%s %s %s %s", ptr[i].name, ptr[i].number, ptr[i].id, ptr[i].pw);
            fputc('\n', fp);
        }


        /* fclose함수는 종료시 오류가 발생하면
        0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
        안내후 프로그램을 종료 */
        state = fclose(fp);
        if (state != 0) {
            printf("File Close Error!\n");
            return 1;
        }
        printf("\n  저장되었습니다. \n");
        return 0;
    }

    else {
        printf("\n  Exit \n");
        return 0;
    }
}



//파일로부터 데이터를 불러오는 함수
int openFile(User* ptr, int* num) {
	int state;
	FILE* fp = fopen("UserInfo.txt", "rt");

	if (fp == NULL) {
		printf("\n");
		return 1;
	}

	//파일에 저장된 데이터를 구조체 배열에 저장
	while (1) {
		fscanf(fp, "%s %s %s %s", ptr[*num].name, ptr[*num].number, ptr[*num].id, ptr[*num].pw);
		if (feof(fp) != 0)
			break;
		(*num)++;
	}


	/* fclose함수는 종료시 오류가 발생하면
	0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
	안내후 프로그램을 종료 */
	state = fclose(fp);
	if (state != 0) {
		printf("File Close Error!\n");
		return 1;
	}

	return 0;
}



//사용자의 정보를 삽입하는 함수 = 회원가입
void insert(User* ptr, int* num)
{
	int i;
	char check_id[30];
	//유저정보가 꽉 차지 않았으면 아이디 생성
	if (*num < MAX_NUM) {
		printf("이름을 입력해주세요: ");
		scanf(" %s", ptr[*num].name);

		printf("전화번호를 입력해주세요: ");
		scanf(" %s", ptr[*num].number);

		while (1) {
			printf("사용하실 아이디를 입력해주세요: ");
			scanf(" %s", check_id);
			for (i = 0; i < MAX_NUM; i++) {
				if (strcmp(check_id, ptr[i].id) == 0) {                      // 텍스트파일에 저장된 문자열들과 비교
					printf("이미 존재하는 아이디입니다.\n\n"); break;        // 중복되는 아이디가 있다면 다시 while문으로
				}
			}
			if (strcmp(check_id, ptr[i].id) != 0)                           //중복되는 아이디가 없다면 while문 탈출 후
				break;
		}
		printf("사용가능한 아이디입니다.\n"); strcpy(ptr[*num].id, check_id);     // 텍스트파일에 입력

		printf("\n사용하실 비밀번호를 입력해주세요: ");
		scanf(" %s", ptr[*num].pw);


		(*num)++;
		printf("회원가입이 완료되었습니다. \n\n");
	}
	//유저 정보가 꽉 차면
	else
		printf("회원수가 꽉 찼습니다. \n\n");
}




void login(User* ptr, int* num)  //로그인
{
	char id[30], pw[30];
	int i;

	//저장된 데이터가 있다면
	if (*num > 0) {
		while (1) {
			printf("아이디를 입력해주세요: "); scanf(" %s", id);
			printf("비밀번호를 입력해주세요: "); scanf(" %s", pw);
			for (i = 0; i < MAX_NUM; i++) {
				if (strcmp(id, ptr[i].id) == 0 && strcmp(pw, ptr[i].pw) == 0) {
					printf("로그인 성공\n\n"); return 1;
				}
			}
			printf("아이디 또는 비밀번호를 틀렸습니다. 다시 로그인 해주세요\n\n"); return 0;
		}
	}
	else
		printf("등록된 아이디가 없습니다...\n회원가입 먼저 해주세요.\n\n");
}

int main(void)
{
    menu();
}