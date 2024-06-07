#include "registerLogin.h"
#include "socket.h"
#define LIMIT 5


void createAccount() {
    char id[20];
    char pw[20];
    char pwCheck[20];
    char name[10];
    int age;

    initiatesocket();

    printf("이름을 입력하세요: ");
    scanf_s("%s", name,10);
    printf("나이를 입력하세요: ");
    scanf_s("%d", &age);
    printf("ID 입력: ");
    scanf_s("%s", id,20);

    while (1) {
        printf("비밀번호 입력 (전체 패스워드 길이는 8자 이상, 특수문자, 대소문자, 숫자 포함): ");
        scanf_s("%s", pw,20);
        printf("비밀번호 확인: ");
        scanf_s("%s", pwCheck, 20);
        
        if (strcmp(pw,pwCheck) != 0) {
            printf("비밀번호가 일치하지 않습니다. 다시 입력하세요.\n");
        }
        else {
            char message[75];
            sprintf_s(message, 75, "MJ:%s,%s,%s,%d", id, pw, name, age);
            printf("%s\n", message);
            char buff[5] = { 0 };
            send(nSocket, message, strlen(message), 0);
            Sleep(3000);
            recv(nSocket, buff, sizeof(buff), 0);
            
            printf("%s\n", buff);
            
            if (buff[3] != '0') {
                printf("이미 가입된 사용자입니다.\n");
                ENDSERVER;
                return;
            }
            else {
                printf("사용자 계정의 생성이 완료되었습니다.\n");
                ENDSERVER;
                return;
            }
        }
    }
}

char* login() {
    int count = 0;
    char id[20];
    char pw[20];
    initiatesocket();
    while (count < LIMIT) {
        printf("아이디를 입력하세요: ");
        scanf_s("%s", id,20);
        printf("비밀번호를 입력하세요: ");
        scanf_s("%s", pw,20);

        char message[45];
        sprintf_s(message, 45, "LI:%s,%s", id, pw);
        char buff[25];
        char* args[2];
        sendandwait(message, buff, args);

        if (args[1][0] == '0') {
            printf("로그인되었습니다.\n");
            return args[0];
        }
        else {
            printf("비밀번호가 틀렸습니다. 다시 시도하세요.\n");
        }
        count++;
    }
    WSACleanup();
    closesocket(nSocket);
    nSocket = NULL;
    return NULL;
}