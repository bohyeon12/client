#include "registerLogin.h"
#include <stdio.h>
#include <string.h>
#include"client.h"
#define LIMIT 5

void createAccount() {
    char id[20];
    char pw[20];
    char pwCheck[20];
    char name[10];
    int age;

    initiatesocket();

    printf("�̸��� �Է��ϼ���: ");
    scanf_s("%s", name,10);
    printf("���̸� �Է��ϼ���: ");
    scanf_s("%d", &age);
    printf("ID �Է�: ");
    scanf_s("%s", id,20);

    while (1) {
        printf("��й�ȣ �Է� (��ü �н����� ���̴� 8�� �̻�, Ư������, ��ҹ���, ���� ����): ");
        scanf_s("%s", pw,20);
        printf("��й�ȣ Ȯ��: ");
        scanf_s("%s", pwCheck,20);

        char message[75];
        sprintf_s(message,75 , "MJ:%s,%s,%s,%d", id, pw, name, age);
        char buff[25];
        char* args[2];
        sendandwait(message,buff,args);

        if (args[1][0] != 0) {
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է��ϼ���.\n");
        }
        else {
            printf("����� ������ ������ �Ϸ�Ǿ����ϴ�.\n");
            WSACleanup();
            closesocket(nSocket);
            nSocket = NULL;
            return;
        }
    }
}

char* login() {
    int count = 0;
    char id[20];
    char pw[20];
    initiatesocket();
    while (count < LIMIT) {
        printf("���̵� �Է��ϼ���: ");
        scanf_s("%s", id,20);
        printf("��й�ȣ�� �Է��ϼ���: ");
        scanf_s("%s", pw,20);

        char message[45];
        sprintf_s(message, 45, "MJ:%s,%s", id, pw);
        char buff[25];
        char* args[2];
        sendandwait(message, buff, args);

        if (args[1][0] == '0') {
            printf("�α��εǾ����ϴ�.\n");
            return args[0];
        }
        else {
            printf("��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �õ��ϼ���.\n");
        }
        count++;
    }
    WSACleanup();
    closesocket(nSocket);
    nSocket = NULL;
    return NULL;
}