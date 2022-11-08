/*사용할 객체 형식 구조체의 구조 및 사용 함수를 기록해두는 헤더파일*/
struct Node{
    int type; //노드의 타입 (1 : User, 2: Book)
    char* data; //노드가 가진 데이터
    struct Node* next; //다음 노드
};
typedef struct Node node; //노드

struct Stack{
    int top; //현재 스택의 정보
    node *data; //현재 노드 정보
};
typedef struct Stack stack; //스택

struct Book
{
    char* title;//도서 명
    char* author;//저자명
    char* publisher;//출판사 명
    int state;//대여 현황
    char* date; //대여 일자
    struct Book* next; //연결된 도서
    
};
typedef struct Book book; //도서

struct User
{
    char* id;//사용자 아이디
    char* pass;//사용자 비밀번호
    struct Book* books;//사용자가 대여한 도서 목록
    struct User* next;
};
typedef struct User user; //사용자

/*스택 관련 함수*/
void Push(stack* Stack); //푸시
node* Pop(stack* Stack); //팝
int isEmpty(stack* Stack); //스택이 비었는지 확인

/*사용자 관련 함수*/
user *addUser(user* userList); //사용자 생성
void deleteUser(user* user); //사용자 제거
int loadUser(char* id, char* pwd,user* User); //사용자 가져오기

/*도서 관련 함수*/
int addBook(book* bookList); //도서 추가
void deleteBook(book *book);  //도서 제거
int loadBooks(book* bookList);  //도서 로딩



