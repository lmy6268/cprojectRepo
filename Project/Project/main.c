//실제 구현은 이곳에서
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

user mainUser;
user *logIn(char *Id, char *pwd)
{	
	user *nowUser;
	nowUser = malloc(sizeof(user));

	if (loadBooks(nowUser->books) == -1 || loadUser(Id,pwd,nowUser) == -1)
	{
		//로드 실패 경우
		printf("데이터를 불러오는 도중 에러가 발생 했습니다.\n");
		return NULL;
	}
	return nowUser;
}

void printBooks(book* books){
	printf("도서명\t저자명\t출판사명\t대출현황\t대출일자\n\n");
	while(books->next!=NULL){
		printf("%s\t%s\t%s\t%s\t%s", books->title, books->author, books->publisher, strState[books->state], books->date);
		books = books->next;
	}
}
