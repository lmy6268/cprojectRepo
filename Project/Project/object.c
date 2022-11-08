#include "object.h"
#include <stdio.h>
#include <string.h>
FILE* filePtr;
user* loadUser(char*id ,char* pwd){
    filePtr = fopen("./userData.txt", "r");
    char *token;
	if(filePtr == NULL){ //파일 로드 실패 시
		printf("파일을 여는 중 오류가 발생했습니다. 프로그램을 다시 실행해 주세요.");
		return -1;
	}

	while(!feof(filePtr)){
		fgets(line, 1000, filePtr);
        token = strtok(line, " ");
        while(token !=NULL){
            
        }
    }
}