#include <stdio.h>
#include "mainspace.h"
#include "registerLogin.h"
#include"socket.h"

// 계좌 정보를 입력하고, DB의 bankInfo 테이블에 저장하는 함수
void inputAccount() {
    char bankName[20];
    char pw[20];
    char bankNumber[11];
    char bankBalance[15];
    int count = 0;
   
    printf("계좌의 은행명을 입력하세요: ");
    scanf_s("%s", bankName,20);
    printf("계좌번호를 입력하세요('-' 제외): ");
    scanf_s("%s", bankNumber,11);
    printf("계좌의 잔액을 입력하세요: ");
    scanf_s("%s", bankBalance,15);

    while (count < LIMIT) {
        printf("사용자 비밀번호를 입력하세요: ");
        scanf_s("%s", pw,20);

        char message[110] = {0,};
        sprintf_s(message, 110, "IA:%s,%s,%s,%s,%s", user, pw, bankNumber, bankName, bankBalance);
        char buff[25] = { 0 };
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

        // 비밀번호 확인 (예: 로그인된 사용자의 비밀번호와 일치하는지 확인)
        if (args[1][0] == '-') { 
            printf("비밀번호가 일치하지 않습니다. 다시 시도하세요.\n");
        }
        else if(args[1][0] == '0') {
            printf("계좌가 입력됐습니다.\n");
            return;
        }
        else if(args[1][0] == '1'){
            printf("오류로 작업이 처리되지 않았습니다.\n");
            return;
        }
        count++;
    }
}

// 계좌 정보를 조회하는 함수
void viewAccount() {
    char message[25] = { 0, };
    sprintf_s(message, 25, "AC:%s", user);
    char buff[255] = { 0 };
    char* args[2] = { NULL,NULL };
    sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

    if(args[1][0] == '\0') {
       printf("계좌정보가 없습니다.\n");
       return;
    }
   else if (args[1][0] == '-') {
        printf("오류로 작업이 처리되지 않았습니다.\n");
        return;
    }
   else {
        int sum = 0;
        printf("%s님의 계좌정보\n계좌번호\t은행\t잔액\n", "1234");
        char* cursor1, * cursor2;
        cursor1 = args[1];
        cursor2 = cursor1 + 1;
        int i = 0;

        while (*cursor2 != '\0' || i == 0) {
            if (*cursor2 == ',') {
                *cursor2 = '\0';
                if (i % 3 == 2) {
                    sum += atoi(cursor1);
                }
                printf("%s%c", cursor1, i++ % 3 == 2 ? '\n' : '\t');
                cursor1 = cursor2+1;
            }
            else if (*cursor2 == '\0') {
                printf("%s\t", cursor1);
                cursor1 = cursor2 + 1;
            }
            cursor2++;
        }
        sum += atoi(cursor1);
        printf("%s\n총잔액 : %d\n", cursor1, sum);
    }
}

// 계좌 정보를 삭제하는 함수
void deleteAccount() {
    char bankNumber[11];
    char bankName[20];
    char pw[20];
    printf("삭제할 계좌 번호를 입력하세요: ");
    scanf_s("%s", bankNumber,11);
    printf("삭제할 계좌 은행명을 입력하세요: ");
    scanf_s("%s", bankName, 20);
    int count = 0;
    

    while (count < LIMIT) {
        printf("사용자 비밀번호를 입력하세요: ");
        scanf_s("%s", pw, 20);

        char message[75] = { 0, };
        sprintf_s(message, 75, "DO:%s,%s,%s,%s", user, pw, bankName, bankNumber);
        char buff[25] = { 0 };
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

        // 비밀번호 확인 (예: 로그인된 사용자의 비밀번호와 일치하는지 확인)
        if (args[1][0] == '-') {
            printf("비밀번호가 일치하지 않습니다. 다시 시도하세요.\n");
        }
        else if (args[1][0] == '0') {
            printf("계좌가 삭제됐습니다.\n");
            return;
        }
        else if (args[1][0] == '1') {
            printf("오류로 작업이 처리되지 않았습니다.\n");
            return;
        }
        count++;
    }
}

void getpercentile() {
    char message[25] = { 0, };
    sprintf_s(message, 25, "GP:%s", user);
    char buff[60] = { 0 };
    char* args[5] = { NULL,NULL,NULL,NULL,NULL };
    sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

    if (args[1][0] == '*') {
        printf("오류로 작업이 처리되지 않았습니다.\n");
        return;
    }
    else if (args[1][0] == '\0') {
        printf("자산정보가 없습니다.\n");
        return;
    }
    else {
        printf("%s님의 나이 : %s\n%c0대 인구 평균자산 : %s원\n", user,args[4],args[4][0],args[3]);
        printf("%s님의 자산 : %s원\n백분위 : 상위 %.1f %%\n", user, args[1], atof(args[2])*100);
    }
}

void logout() {
    ENDSERVER;
    extern char* user;
    user = NULL;
    printf("로그아웃 되었습니다.\n");
}