//실제 구현은 이곳에서
#include "main.h"
#include <stdio.h>
#include <curses.h>

FILE *filePtr; //파일을 열기 위한 포인터
char *line; //현재 읽어들인 라인

int ReadData(user* User, book* Book){
	filePtr = fopen("./userData.txt", "r");
	
}



int main(void)
{
	printf("hi");
	clear();
	return 0;
}