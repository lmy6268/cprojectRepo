//사용하는 헤더파일 및 함수 정의
#include "object.h"

//회원관리
user* signIn(); //회원가입
user *logIn(char *Id, char *pwd); //로그인
void logOut(); //로그아웃

//대여 관리
int borrowBook(book *book, user *user); //도서 대여
int returnBook(book *book, user *user); //도서 반납

//파일 관리

int ReadData(user *User, book *Book);