#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//���� ���������� ���� �ϱ����� 100�̶� ���ڸ�
//MAX_NUM���� ����, 100�� 200���� �ٲٸ�
//MAX_NUM�� 200�� ��
#define MAX_NUM 100



//������� ������ �����ϴ� ����ü
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
    User user[MAX_NUM]; //����� ������ ������ ����ü �迭
    int person = 0; //����� user��



    openFile(user, &person);//����� �����͸� �ҷ����� �Լ�



    //�޴� ����
    while (1) {
        printf("***** �޴� ***** \n");
        printf("1. ȸ������ \n");
        printf("2. �α��� \n");
        printf("3. �����ϰ� ���� \n");

        printf("�޴��� �����ϼ���: ");
        scanf("%d", &input);



        if (input == 1) {
            printf("\n[ȸ������] \n");
            insert(user, &person);
        }
        else if (input == 2) {
            printf("\n[�α���] \n");
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



//�����͸� ���Ͽ� �����ϴ� �Լ�
int saveFile(User* ptr, int* num) {

    if (*num > 0) {
        int i, state;
        FILE* fp = fopen("UserInfo.txt", "wt");


        /* fopen�Լ��� �����߻��� NULL�� �����ϹǷ�
        ���� ���� �� �����߻��� ���α׷��� ���� */
        if (fp == NULL) {
            printf("File Open Error!\n");
            return 1;
        }



        //����ü �迭�� ����� �����͸� ���Ͽ� ����
        //�ٹٲ����� �����Ͽ� ����
        for (i = 0; i < *num; i++) {
            fprintf(fp, "%s %s %s %s", ptr[i].name, ptr[i].number, ptr[i].id, ptr[i].pw);
            fputc('\n', fp);
        }


        /* fclose�Լ��� ����� ������ �߻��ϸ�
        0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
        �ȳ��� ���α׷��� ���� */
        state = fclose(fp);
        if (state != 0) {
            printf("File Close Error!\n");
            return 1;
        }
        printf("\n  ����Ǿ����ϴ�. \n");
        return 0;
    }

    else {
        printf("\n  Exit \n");
        return 0;
    }
}



//���Ϸκ��� �����͸� �ҷ����� �Լ�
int openFile(User* ptr, int* num) {
	int state;
	FILE* fp = fopen("UserInfo.txt", "rt");

	if (fp == NULL) {
		printf("\n");
		return 1;
	}

	//���Ͽ� ����� �����͸� ����ü �迭�� ����
	while (1) {
		fscanf(fp, "%s %s %s %s", ptr[*num].name, ptr[*num].number, ptr[*num].id, ptr[*num].pw);
		if (feof(fp) != 0)
			break;
		(*num)++;
	}


	/* fclose�Լ��� ����� ������ �߻��ϸ�
	0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
	�ȳ��� ���α׷��� ���� */
	state = fclose(fp);
	if (state != 0) {
		printf("File Close Error!\n");
		return 1;
	}

	return 0;
}



//������� ������ �����ϴ� �Լ� = ȸ������
void insert(User* ptr, int* num)
{
	int i;
	char check_id[30];
	//���������� �� ���� �ʾ����� ���̵� ����
	if (*num < MAX_NUM) {
		printf("�̸��� �Է����ּ���: ");
		scanf(" %s", ptr[*num].name);

		printf("��ȭ��ȣ�� �Է����ּ���: ");
		scanf(" %s", ptr[*num].number);

		while (1) {
			printf("����Ͻ� ���̵� �Է����ּ���: ");
			scanf(" %s", check_id);
			for (i = 0; i < MAX_NUM; i++) {
				if (strcmp(check_id, ptr[i].id) == 0) {                      // �ؽ�Ʈ���Ͽ� ����� ���ڿ���� ��
					printf("�̹� �����ϴ� ���̵��Դϴ�.\n\n"); break;        // �ߺ��Ǵ� ���̵� �ִٸ� �ٽ� while������
				}
			}
			if (strcmp(check_id, ptr[i].id) != 0)                           //�ߺ��Ǵ� ���̵� ���ٸ� while�� Ż�� ��
				break;
		}
		printf("��밡���� ���̵��Դϴ�.\n"); strcpy(ptr[*num].id, check_id);     // �ؽ�Ʈ���Ͽ� �Է�

		printf("\n����Ͻ� ��й�ȣ�� �Է����ּ���: ");
		scanf(" %s", ptr[*num].pw);


		(*num)++;
		printf("ȸ�������� �Ϸ�Ǿ����ϴ�. \n\n");
	}
	//���� ������ �� ����
	else
		printf("ȸ������ �� á���ϴ�. \n\n");
}




void login(User* ptr, int* num)  //�α���
{
	char id[30], pw[30];
	int i;

	//����� �����Ͱ� �ִٸ�
	if (*num > 0) {
		while (1) {
			printf("���̵� �Է����ּ���: "); scanf(" %s", id);
			printf("��й�ȣ�� �Է����ּ���: "); scanf(" %s", pw);
			for (i = 0; i < MAX_NUM; i++) {
				if (strcmp(id, ptr[i].id) == 0 && strcmp(pw, ptr[i].pw) == 0) {
					printf("�α��� ����\n\n"); return 1;
				}
			}
			printf("���̵� �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �α��� ���ּ���\n\n"); return 0;
		}
	}
	else
		printf("��ϵ� ���̵� �����ϴ�...\nȸ������ ���� ���ּ���.\n\n");
}

int main(void)
{
    menu();
}