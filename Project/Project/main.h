//사용하는 헤더파일 및 함수 정의
#include "object.h"


//상태 표시 열거형
enum state{ busy, available };
char strState[2][20] = {"대출 중","대여 가능"};

//전역변수
user mainUser; //현재 사용자
//회원관리
user* signIn(); //회원가입
user *logIn(char *Id, char *pwd); //로그인
void logOut(); //로그아웃

//대여 관리
int borrowBook(book *book, user *user); //도서 대여
int returnBook(book *book, user *user); //도서 반납

//파일 관리

int ReadData(user *User, book *Book);

//화면출력
void printBooks(book *Books);