#include <stdio.h>
#include "registerLogin.h"
//#include "mainspace.h"
#include "socket.h"


int main() {
    int menuNum = 0;
    while (1) {
        if (user == NULL) {
            printf("1: �α���   2: ȸ������\n");
            scanf_s("%d", &menuNum);
            if (menuNum == 1) {
                user = login();
                
            }
            else if (menuNum == 2) {
                createAccount();
                
            }
            else {
                printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
            }
        }
        else {
            printf("1. ���� ���� �Է�\n");
            printf("2. ���� ��ȸ\n");
            printf("3. ���� ���� ����\n");
            printf("4. �α׾ƿ�\n");
            printf("���Ͻô� ������ ��ȣ�� �Է��ϼ���: ");
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
                printf("�α׾ƿ� �Ǿ����ϴ�.\n");
                return;
            default:
                printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            }
        }
        
    }
    return 0;
}