#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *filePtr;
char *token, *line;
//사용자를 불러온다.
int loadUser(char *id, char *pwd, user *User)
{
    filePtr = fopen("./userData.txt", "r");
    char *tmpId, *tmpPwd; //
    if (filePtr == NULL)
    { //파일 로드 실패 시
        printf("파일을 여는 중 오류가 발생했습니다. 프로그램을 다시 실행해 주세요.");
        return -1;
    }

    while (!feof(filePtr))
    {
        int idx = 0;
        fgets(line, 1000, filePtr);
        token = strtok(line, " ");

        while (token != NULL)
        {
            if (idx == 0)
                strcpy(tmpId, token);
            else if (idx == 1)
                strcpy(tmpPwd, token);
            idx++;
            token = strtok(NULL, " ");
        }

        //일치하는 데이터가 있는 경우
        if (!strcmp(id, tmpId) && !strcmp(pwd, tmpPwd))
        {
            User = (user*)malloc(sizeof(user)); //크기 할당
            //유저 데이터를 저장한다.
            return 0; //정상 로딩
        }
    }
    fclose(filePtr);
}

//도서를 가져온다.
int loadBooks(book *bookList)
{
    filePtr = fopen("./bookData.txt", "r");
    int i;
    if (filePtr == NULL)
    { //파일 로드 실패 시
        printf("파일을 여는 중 오류가 발생했습니다. 프로그램을 다시 실행해 주세요.");
        return -1;
    }
    while (!feof(filePtr))
    {
        int idx = 0;
        book *newBook;
        newBook = (book *)malloc(sizeof(book));
        fgets(line, 1000, filePtr);
        token = strtok(line, " "); //제목 / 저자 / 출판사 / 대여일자 /

        while (token != NULL)
        {
            switch (idx)
            {
            case 0:
                strcpy(newBook->title, token);
                break;
            case 1:
                strcpy(newBook->author, token);
                break;
            case 2:
                strcpy(newBook->publisher, token);
                break;
            case 3:
                strcpy(newBook->date, token);
                break;
            case 4:
                newBook->state = atoi(token);
                break;
            default:
                break;
            }
            idx++;
        }
        bookList->next = newBook;
        bookList = newBook; // 포인터 이동
        i++;
    }

    fclose(filePtr);
}
//도서를 추가한다.
int addBook(book *BookList){
    book newBook;
    printf("도서명 / 저자 / 출판사 순으로 입력해주세요. : ");
    scanf("%s %s %s",newBook.title,newBook.author,newBook.publisher);
    newBook.date = "";
    BookList->next = &newBook;
    BookList = &newBook;
    filePtr = fopen("./bookData.txt","a");
    if(filePtr == NULL) {
        printf("파일을 여는 도중 에러가 발생하였습니다.\n");
        return -1;
    }
    fputs(newBook, filePtr);
    fclose(filePtr);
    return 0;
}
