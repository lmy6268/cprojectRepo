/*
user.h���� �����ص� �Լ� �� �������� ������ ���� c��� �����Դϴ�.
*/
#include "user.h"

int openFile(User* ptr, int* num) {
	int state;
	FILE* fp = fopen("UserInfo.txt", "rt");

	if (fp == NULL) {
		printf("\n");
		return 1;
	}

	//���Ͽ� ����� �����͸� ����ü �迭�� ����
	while (fscanf(fp, "%d %s %s %s %s ", &ptr[*num].orderNum, ptr[*num].name, ptr[*num].number, ptr[*num].id, ptr[*num].pw)!=-1) {
		for (int i = 0; i < 3; i++) fscanf(fp, "%d, ", &ptr[*num].books[i]);
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
		ptr[*num].orderNum = *num; //���� ��ȣ

		for (int j = 0; j < 3; j++) {
			ptr[*num].books[j] = -1; //�ʱ�ȭ
		}

		printf("ȸ�������� �Ϸ�Ǿ����ϴ�. \n\n");
		(*num)++;
	}
	//���� ������ �� ����
	else
		printf("ȸ������ �� á���ϴ�. \n\n");
}

// �����͸� ���Ͽ� �����ϴ� �Լ�
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
			fprintf(fp, "%d %s %s %s %s ", ptr[i].orderNum, ptr[i].name, ptr[i].number, ptr[i].id, ptr[i].pw);
			for (int j = 0; j < 3; j++) {
				fprintf(fp, "%d, ", ptr[i].books[j]);
			}
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
}


int login(User* ptr, int* num)  //�α���
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
					return i; //��ġ�� ��ȯ
				}
			}
			printf("���̵� �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �α��� ���ּ���\n\n");
			return -1;
		}
	}
	else
		printf("��ϵ� ���̵� �����ϴ�...\nȸ������ ���� ���ּ���.\n\n");
	return -1;
}

