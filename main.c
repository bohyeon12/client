#include <stdio.h>
#include "registerLogin.h"
#include "mainspace.h"
#include "socket.h"

char* user = NULL;
int main() {
    int menuNum = 0;
    while (1) {
        if (user == NULL) {
            printf("1: �α���   2: ȸ������ 3. ����\n");
            scanf_s("%d", &menuNum);
            if (menuNum == 1) {
                login();            }
            else if (menuNum == 2) {
                createAccount();
            }
            else if (menuNum == 3) {
                printf("���α׷��� ����˴ϴ�.\n");
                exit(0);
            }
            else {
                printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            }
        }
        else {
            printf("1. ���� ���� �Է�\n");
            printf("2. ���� ��ȸ\n");
            printf("3. ���� ���� ����\n");
            printf("4. ���ɴ� ��� �ڻ� ����� ���ϱ�\n");
            printf("5. �α׾ƿ�\n");
            printf("���Ͻô� ������ ��ȣ�� �Է��ϼ���: ");
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
                printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            }
        }
        
    }
    return 0;
}