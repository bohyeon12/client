#include <stdio.h>
#include "registerLogin.h"
//#include "mainspace.h"
#include "socket.h"


int main() {
    int menuNum = 0;
    while (1) {
        if (user == NULL) {
            printf("1: 로그인   2: 회원가입\n");
            scanf_s("%d", &menuNum);
            if (menuNum == 1) {
                user = login();
                
            }
            else if (menuNum == 2) {
                createAccount();
                
            }
            else {
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
            }
        }
        else {
            printf("1. 계좌 정보 입력\n");
            printf("2. 계좌 조회\n");
            printf("3. 계좌 정보 삭제\n");
            printf("4. 로그아웃\n");
            printf("원하시는 서비스의 번호를 입력하세요: ");
            scanf_s("%d", &menuNum);

            switch (menuNum) {
            case 1:
               // inputAccount();
                break;
            case 2:
               // viewAccount();
                break;
            case 3:
               // deleteAccount();
                break;
            case 4:
                printf("로그아웃 되었습니다.\n");
                return;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
            }
        }
        
    }
    return 0;
}