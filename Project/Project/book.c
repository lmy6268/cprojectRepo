#include "book.h"

char state[2][10] = { "대출가능"," 대여중 " }; 
char bar[216] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

void findBooks(BOOK *books, int type, char *keyword, int *returnList, int *length) {
	int idx = 0;
	for (int i = 0; strcmp((books + i)->title, ""); i++) {
		switch (type) {
		case 0: //도서명으로 검색
			if (strstr((books + i)->title, keyword) != NULL) *(returnList + idx++) = i + 1;
			break;
		case 1://출판사명으로 검색
			if (strstr((books + i)->publisher, keyword) != NULL) *(returnList + idx++) = i + 1;
			break;
		case 2:// 저자명으로 검색
			if (strstr((books + i)->author, keyword) != NULL)*(returnList + idx++) = i + 1;
			break;
		case 3: //통합검색
			if (strstr((books + i)->author, keyword) != NULL || strstr((books + i)->publisher, keyword) != NULL || strstr((books + i)->title, keyword) != NULL)*(returnList + idx++) = i + 1;
		default:
			break;
		}
	}
	*length = idx; //검색 결과의 길이를 저장 
}
void ReadBooks(BOOK *books) {
	FILE *fp;
	char tmp[MAX_NUM * 3] = { 0 };
	char *token = 0;
	int idx = 0, tmpIdx = 0;
	if ((fp = fopen("books.txt", "r")) == NULL) {
		fprintf(fp, "에러가 생겼습니다.");
		exit(1);
	}
	while (!feof(fp)) {
		tmpIdx = 0;
		fgets(tmp, MAX_NUM * 3, fp);
		if (strcmp("상품명\t출판사/제작사\t저자/아티스트\t대여상태\n", tmp)) //첫줄은 무시
		{
			token = strtok(tmp, "\t\n"); // //나 엔터키를 기준으로 토크나이징 진행
			while (token != NULL) {
				switch (tmpIdx) {
				case 0: //첫번째 값은 도서명
					strcpy((books + idx)->title, token);
					break;
				case 1: //두번째 값은 출판사명
					strcpy((books + idx)->publisher, token);
					break;
				case 2: //세번째 값은 저자명
					strcpy((books + idx)->author, token);
					break;
				case 3: //마지막 값은 도서상태 
					(books + idx)->state = atoi(token);
					break;
				default:
					break;
				}
				token = strtok(NULL, "\t\n"); //현재 줄에서 마저 토크나이징 진행
				tmpIdx++; //다음 값으로 이동 
			}
			idx++;
		}
	}
	fclose(fp);
}
void drawBooks(BOOK *books, int *list) {
	printf("%s", bar);
	printf("| %s |%-80s |%-80s|%-30s | %s |\n", "번호", "                                       도서명", "                                       저자명", "            출판사명", "  상태  ");
	printf("%s", bar);
	//검색결과인 경우
	if (list != NULL) {
		for (int t = 0; *(list + t) != 0; t++) {
			int i = *(list + t) - 1;
			printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", t + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
			printf("%s", bar);
		}
	}
	//전체 리스트인 경우 
	else for (int i = 0; strcmp((books + i)->title, ""); i++) {
		printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", i + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
		printf("%s", bar);
	}
}

void rentBook(BOOK *books, int idx) {
	FILE *fp;
	int i = 0;
	if ((fp = fopen("./books.txt", "w")) == NULL) {
		fprintf(fp, "에러가 생겼습니다.");
		exit(1);
	}
	(books + idx)->state = 1;
	fprintf(fp, "상품명\t출판사/제작사\t저자/아티스트\t대여상태\n");
	while (1) {
		if (!strcmp((books + i)->title, ""))break;
		if (!strcmp((books + i + 1)->title, ""))fprintf(fp, "%s\t%s\t%s\t%d", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		else fprintf(fp, "%s\t%s\t%s\t%d\n", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		i++;
	}
	fclose(fp);
	printf("%s 대여가 완료되었습니다.!\n", (books + idx)->title);
}

void eliminateWord(char *words, char *data) {
	char* ptr = strstr(words, data);  // simple이 존재하는 위치를 찾음
	while (ptr != NULL) {
		strncpy(ptr, " ", 1);
		ptr = strstr(ptr + 1, data);
	}
}