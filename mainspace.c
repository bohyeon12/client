#include <stdio.h>
#include "mainspace.h"
#include "registerLogin.h"
#include"socket.h"

// ���� ������ �Է��ϰ�, DB�� bankInfo ���̺� �����ϴ� �Լ�
void inputAccount() {
    char bankName[20];
    char pw[20];
    char bankNumber[11];
    char bankBalance[15];
    int count = 0;
   
    printf("������ ������� �Է��ϼ���: ");
    scanf_s("%s", bankName,20);
    printf("���¹�ȣ�� �Է��ϼ���('-' ����): ");
    scanf_s("%s", bankNumber,11);
    printf("������ �ܾ��� �Է��ϼ���: ");
    scanf_s("%s", bankBalance,15);

    while (count < LIMIT) {
        printf("����� ��й�ȣ�� �Է��ϼ���: ");
        scanf_s("%s", pw,20);

        char message[110] = {0,};
        sprintf_s(message, 110, "IA:%s,%s,%s,%s,%s", user, pw, bankNumber, bankName, bankBalance);
        char buff[25] = { 0 };
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

        // ��й�ȣ Ȯ�� (��: �α��ε� ������� ��й�ȣ�� ��ġ�ϴ��� Ȯ��)
        if (args[1][0] == '-') { 
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �õ��ϼ���.\n");
        }
        else if(args[1][0] == '0') {
            printf("���°� �Էµƽ��ϴ�.\n");
            return;
        }
        else if(args[1][0] == '1'){
            printf("������ �۾��� ó������ �ʾҽ��ϴ�.\n");
            return;
        }
        count++;
    }
}

// ���� ������ ��ȸ�ϴ� �Լ�
void viewAccount() {
    char message[25] = { 0, };
    sprintf_s(message, 25, "AC:%s", user);
    char buff[255] = { 0 };
    char* args[2] = { NULL,NULL };
    sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

    if(args[1][0] == '\0') {
       printf("���������� �����ϴ�.\n");
       return;
    }
   else if (args[1][0] == '-') {
        printf("������ �۾��� ó������ �ʾҽ��ϴ�.\n");
        return;
    }
   else {
        int sum = 0;
        printf("%s���� ��������\n���¹�ȣ\t����\t�ܾ�\n", "1234");
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
        printf("%s\n���ܾ� : %d\n", cursor1, sum);
    }
}

// ���� ������ �����ϴ� �Լ�
void deleteAccount() {
    char bankNumber[11];
    char bankName[20];
    char pw[20];
    printf("������ ���� ��ȣ�� �Է��ϼ���: ");
    scanf_s("%s", bankNumber,11);
    printf("������ ���� ������� �Է��ϼ���: ");
    scanf_s("%s", bankName, 20);
    int count = 0;
    

    while (count < LIMIT) {
        printf("����� ��й�ȣ�� �Է��ϼ���: ");
        scanf_s("%s", pw, 20);

        char message[75] = { 0, };
        sprintf_s(message, 75, "DO:%s,%s,%s,%s", user, pw, bankName, bankNumber);
        char buff[25] = { 0 };
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

        // ��й�ȣ Ȯ�� (��: �α��ε� ������� ��й�ȣ�� ��ġ�ϴ��� Ȯ��)
        if (args[1][0] == '-') {
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �õ��ϼ���.\n");
        }
        else if (args[1][0] == '0') {
            printf("���°� �����ƽ��ϴ�.\n");
            return;
        }
        else if (args[1][0] == '1') {
            printf("������ �۾��� ó������ �ʾҽ��ϴ�.\n");
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
        printf("������ �۾��� ó������ �ʾҽ��ϴ�.\n");
        return;
    }
    else if (args[1][0] == '\0') {
        printf("�ڻ������� �����ϴ�.\n");
        return;
    }
    else {
        printf("%s���� ���� : %s\n%c0�� �α� ����ڻ� : %s��\n", user,args[4],args[4][0],args[3]);
        printf("%s���� �ڻ� : %s��\n����� : ���� %.1f %%\n", user, args[1], atof(args[2])*100);
    }
}

void logout() {
    ENDSERVER;
    extern char* user;
    user = NULL;
    printf("�α׾ƿ� �Ǿ����ϴ�.\n");
}