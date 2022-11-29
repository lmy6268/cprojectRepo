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

void drawBooks(BOOK *books, int *list, int size,int type) {
	if (list != NULL) {
		if (type == 0) //검색 결과
		{
			char cmdLine[100];
			sprintf(cmdLine, "mode con cols=250 lines=%d | title 도서 검색 결과 ", (size + 1) * 10);
			system(cmdLine); // 콘솔창 크기 및 제목 설정
			printf("< 도서 검색 > \n");
			printf("%s", bar);
			printf("| %s |%-80s |%-80s|%-30s | %s |\n", "번호", "                                       도서명", "                                       저자명", "            출판사명", "  상태  ");
			printf("%s", bar);
			for (int t = 0; *(list + t) != 0; t++) {
				int i = *(list + t) - 1;
				printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", t + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
				printf("%s", bar);
			}
		}
		else if (type == 1) //나의 대여 목록

		{
			system("mode con cols=250 lines=40 | title 나의 대여 목록"); // 콘솔창 크기 및 제목 설정
			printf("< 나의 대여 목록 > \n");
			printf("%s", bar);
			printf("| %s |%-80s |%-80s|%-30s | %s |\n", "번호", "                                       도서명", "                                       저자명", "            출판사명", "  상태  ");
			printf("%s", bar);
			for (int t = 0; *(list + t) != 0 && *(list + t) != -1; t++) {
				int i = *(list + t) - 1;
				printf("|  %02d  |%-80s |%-80s|%-30s | %s |\n", t + 1, (books + i)->title, (books + i)->author, (books + i)->publisher, state[(books + i)->state]);
				printf("%s", bar);
			}
		}
	}
	//전체 리스트인 경우 
	else {
		system("mode con cols=250 lines=400 | title 도서 대여"); // 콘솔창 크기 및 제목 설정
		printf("< 베스트 셀러 도서 > \n");
		printf("%s", bar);
		printf("| %s |%-80s |%-80s|%-30s | %s |\n", "번호", "                                       도서명", "                                       저자명", "            출판사명", "  상태  ");
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

	if ((fp = fopen("./UserInfo.txt", "w")) == NULL) {
		fprintf(fp, "에러가 생겼습니다.");
		exit(1);
	}
	i = 0;
	while (1) {
		if (i >= 3) break;
		else if (*((user->books) + i) == -1)
		{
			*((user->books) + i) = idx + 1; //대여한 도서를 리스트에 담음
			break;
		}
		i++;
	}

	//마지막 사용자를 어떻게 파악할까,,, 
	User *users = user - (user->orderNum);
	for (i = 0 ; strcmp((users+i) ->id,""); i++) {
		fprintf(fp, "%d %s %s %s %s ", (users + i)->orderNum,(users + i)->name, (users + i)->number, (users + i)->id, (users + i)->pw);
		for (int j = 0; j < 3; j++) {
			fprintf(fp, "%d, ", *((users + i)->books + j));
		}
		fputc('\n', fp);
	}
	int state = fclose(fp);

	printf("%s 대여가 완료되었습니다.!\n", (books + idx)->title);
}

void returnBook(BOOK *books, int idx, User *user){
	FILE *fp;
	int i = 0;
	if ((fp = fopen("./books.txt", "w")) == NULL) {
		fprintf(fp, "에러가 생겼습니다.");
		exit(1);
	}
	(books + idx)->state = 0;
	fprintf(fp, "상품명\t출판사/제작사\t저자/아티스트\t대여상태\n");
	while (1) {
		if (!strcmp((books + i)->title, ""))break;
		if (!strcmp((books + i + 1)->title, ""))fprintf(fp, "%s\t%s\t%s\t%d", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		else fprintf(fp, "%s\t%s\t%s\t%d\n", (books + i)->title, (books + i)->publisher, (books + i)->author, (books + i)->state);
		i++;
	}
	fclose(fp);

	if ((fp = fopen("./UserInfo.txt", "w")) == NULL) {
		fprintf(fp, "에러가 생겼습니다.");
		exit(1);
	}
	int index = -1;
	int tmp = 0;
	for (int i = 0; i < 3; i++) {
		//위치 찾기 
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

		 *((user->books) + 2) = -1; //끝에 데이터를 옮기고 초기화 

		break;
	case 1:
		tmp = *((user->books) + 1);
		*((user->books) + 1) = *((user->books) + 2);
		*((user->books) + 2) = tmp;

		*((user->books) + 2) = -1; //끝에 데이터를 옮기고 초기화 
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

	printf("%s 반납이 완료되었습니다.!\n", (books + idx)->title);
	Sleep(1000);
}


// 데이터 가져올 때 필요없는 문자를 제거하기 위함.
void eliminateWord(char *words, char *data) {
	char* ptr = strstr(words, data);  // simple이 존재하는 위치를 찾음
	while (ptr != NULL) {
		strncpy(ptr, " ", 1);
		ptr = strstr(ptr + 1, data);
	}
}