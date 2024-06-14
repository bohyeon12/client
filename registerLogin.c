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
    printf("------------------------------------------------------\n");
    printf("Put your name: ");
    scanf_s("%s", name,10);
    printf("Put your age: ");
    scanf_s("%d", &age);
    printf("Put your ID: ");
    scanf_s("%s", id,20);

    while (1) {
        printf("Put your password : ");
        scanf_s("%s", pw,20);
        printf("Put your password again: ");
        scanf_s("%s", pwCheck, 20);
        
        if (strcmp(pw,pwCheck) != 0) {
            printf("Your password is not assured. Try again\n");
        }
        else {
            char message[75];
            sprintf_s(message, 75, "MJ:%s,%s,%s,%d", id, pw, name, age);
            char buff[5] = { 0 };
            char* args[1] = { NULL };
            sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

            if(args[0][0] == '1'){
                printf("This ID already exist.\n");
                ENDSERVER;
                return;
            }
            else if(args[0][0] == '0'){
                printf("Sign up completed\n");
                ENDSERVER;
                return;
            }
        }
    }
}

void login() {
    printf("------------------------------------------------------\n");
    int count = 0;
    char id[20];
    char pw[20];
    initiatesocket();
    while (count < LIMIT) {
        printf("Put your ID : ");
        scanf_s("%s", id,20);
        printf("Put your password : ");
        scanf_s("%s", pw,20);

        char message[45];
        sprintf_s(message, 45, "LI:%s,%s", id, pw);
        char buff[25] = {0,};
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args)/sizeof(char*));

        if (args[1][0] == '0') {
            extern char* user;
            user = (char*)malloc(sizeof(char)*strlen(args[0]) + 1);
            strcpy_s(user, strlen(args[0]) + 1, args[0]);
            return ;
        }
        else {
            printf("Wrong password. Try again. \n");
        }
        count++;
    }
    WSACleanup();
    closesocket(nSocket);
    nSocket = NULL;
    return NULL;
}