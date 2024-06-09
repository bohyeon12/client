#include <stdio.h>
#include "registerLogin.h"
#include "mainspace.h"
#include "socket.h"

char* user = NULL;
int main() {
    int menuNum = 0;
    while (1) {
        if (user == NULL) {
            printf("1: 로그인   2: 회원가입 3. 종료\n");
            scanf_s("%d", &menuNum);
            if (menuNum == 1) {
                login();            }
            else if (menuNum == 2) {
                createAccount();
            }
            else if (menuNum == 3) {
                printf("프로그램이 종료됩니다.\n");
                exit(0);
            }
            else {
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
            }
        }
        else {
            printf("1. 계좌 정보 입력\n");
            printf("2. 계좌 조회\n");
            printf("3. 계좌 정보 삭제\n");
            printf("4. 연령대 대비 자산 백분위 구하기\n");
            printf("5. 로그아웃\n");
            printf("원하시는 서비스의 번호를 입력하세요: ");
            scanf_s("%d", &menuNum);

            switch (menuNum) {
            case 1:
               inputAccount();
                break;
            case 2:
               viewAccount();
                break;
            case 3:
               deleteAccount();
                break;
            case 4:
                getpercentile();
                break;
            case 5:
                logout();
                break;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
            }
        }
        
    }
    return 0;
}