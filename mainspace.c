#include <stdio.h>
#include "mainspace.h"
#include"socket.h"
#include "callapi.h"
#include "cJSON.h"
// 계좌 정보를 입력하고, DB의 bankInfo 테이블에 저장하는 함수
void inputAccount() {
    char bankName[20];
    char pw[20];
    char bankNumber[11];
    char bankBalance[15];
    int count = 0;
   
    printf("Put your bank : ");
    scanf_s("%s", bankName,20);
    printf("Put your account number : ");
    scanf_s("%s", bankNumber,11);
    printf("Put the deposit in the account: ");
    scanf_s("%s", bankBalance,15);

    while (count < LIMIT) {
        printf("Put your password: ");
        scanf_s("%s", pw,20);

        char message[110] = {0,};
        sprintf_s(message, 110, "IA:%s,%s,%s,%s,%s", user, pw, bankNumber, bankName, bankBalance);
        char buff[25] = { 0 };
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

        // 비밀번호 확인 (예: 로그인된 사용자의 비밀번호와 일치하는지 확인)
         if (args[1][0] == '-') { 
             printf("Wrong password. Try again.\n");
         }
         else if(args[1][0] == '0') {
             printf("Input Account completed\n");
             return;
         }
         else if(args[1][0] == '1'){

             printf("There was an error during the process.\n");
             return;
         }
         count++;
     }
}

// 계좌 정보를 조회하는 함수
void viewAccount() {
    char message[25] = { 0, };
    sprintf_s(message, 25, "AC:%s", user);
    char buff[500] = { 0 };
    char copy[500] = { 0, };
    char* args[2] = { NULL,NULL };
    sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));
    
    char* currency = "KRW";
    double exchangerate = 1.0;
    cJSON* item = NULL;
    cJSON* json = NULL;
    char* cur_unit[23] = { NULL, };
    double deal_bas_rs[23] = { 0, };
    int i = 0;
    json = getexchangerate();
    cJSON_ArrayForEach(item, json) {
        cur_unit[i] = cJSON_GetObjectItem(item, "cur_unit")->valuestring;
        deal_bas_rs[i] = manufactdeal_bas_r(cJSON_GetObjectItem(item, "deal_bas_r")->valuestring);
        printf("cur uint : %s | deal_bas_rs : %f\n", cur_unit[i], deal_bas_rs[i]);
        i++;
    }
    
    if(args[1][0] == '\0') {
       printf("That account doesn't exist.\n");
       return;
    }
    else if (args[1][0] == '-') {
        printf("There was an error during the process.\n");
         return;
    }
    else {
        int menuNum = 0;
        while (1) {
            boolean check = FALSE;
            for (i = 0; i < 500; i++) {
                if (buff[i] == '\0' && check) break;
                else if (buff[i] == '\0') check = TRUE;
                else check = FALSE;
                copy[i] = buff[i];
            }
            long sum = 0;
            printf("%s's account information\nAccount number\tBank\tDeposit\t*currency : %s\n", args[0], currency);
            char* cursor1, * cursor2;
            cursor1 = copy+(args[1]-args[0]) + 3;
            cursor2 = cursor1 + 1;
            i = 0;

            while (*cursor2 != '\0' || i == 0) {
                 if (*cursor2 == ',') {
                     *cursor2 = '\0';
                     if (i++ % 3 == 2) {
                         sum += printdeposit(cursor1, exchangerate);
                     } else printf("%s%c", cursor1, '\t');
                     cursor1 = cursor2 + 1;
                 }
                 else if (*cursor2 == '\0') {
                     printf("%s\t", cursor1);
                     cursor1 = cursor2 + 1;
                 }
                 cursor2++;
             }
            sum += printdeposit(cursor1, exchangerate);
             printf("Total asset :%d\n", sum);
             printf("1: Change currency   2: Go back\n");
             scanf_s("%d", &menuNum);
             if (menuNum == 1) {
                 if (json == NULL) {
                     printf("Cannot bring currency exchange rate\n");
                     continue;
                 }
                 for (i = 0; i < 23; i++) {
                     printf("%d. %s\n", 1 + i, cur_unit[i]);
                 }
                 printf("Choose one among these currency\n");
                 scanf_s("%d", &menuNum);
                  if (menuNum > 0 && menuNum <= 23) {
                     if (cur_unit[i] == NULL) {
                         fprintf(stderr, "There is no information about this currency.\n");
                         continue;
                     }
                     exchangerate = deal_bas_rs[menuNum-1];
                     currency = cur_unit[menuNum-1];
                     printf("exchange : %f\n", exchangerate);
                 }
                 else {
                     printf("Wrong input. Try again\n");
                 }
             }
             else if (menuNum == 2) {
                 cJSON_Delete(json);
                 return;
             }
             else {
                 printf("Wrong input. Try again\n");
             }
         }  
    }
}

// 계좌 정보를 삭제하는 함수
void deleteAccount() {
    char bankNumber[11];
    char bankName[20];
    char pw[20];
    printf("Put the account number : ");
    scanf_s("%s", bankNumber,11);
    printf("Put the bank : ");
    scanf_s("%s", bankName, 20);
    int count = 0;
    

    while (count < LIMIT) {
        printf("Put your password : ");
        scanf_s("%s", pw, 20);

        char message[75] = { 0, };
        sprintf_s(message, 75, "DO:%s,%s,%s,%s", user, pw, bankName, bankNumber);
        char buff[25] = { 0 };
        char* args[2] = { NULL,NULL };
        sendandwait(message, buff, args, sizeof(buff), sizeof(args) / sizeof(char*));

        // 비밀번호 확인 (예: 로그인된 사용자의 비밀번호와 일치하는지 확인)
        if (args[1][0] == '-') {
            printf("Wrong password. Try gain\n");
        }
        else if (args[1][0] == '0') {
            printf("Account deleted.\n");
            return;
        }
        else if (args[1][0] == '1') {
            printf("There was an error during the process.\n");
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
        printf("There was an error during the process.\n");
        return;
    }
    else if (args[1][0] == '\0') {
        printf("Account information is not found.\n");
        return;
    }
    else {
        printf("%s's age : %s\n%c0s average asset : %s \n", user, args[4], args[4][0], args[3]);
        printf("%s's asset : %s\npercentile : Upper %.1f %%\n", user, args[1], atof(args[2])*100);
    }
}

void logout() {
    ENDSERVER;
    extern char* user;
    user = NULL;
    printf("Logged out.\n");
}

long printdeposit(char* deposit, double exr) {
    long value = atol(deposit) /exr;
    printf("%ld\n", value);
    return value;
}

double manufactdeal_bas_r(char* deal_bas_r) {
    char* cursor1 = deal_bas_r+1;
    char* cursor2 = deal_bas_r + 1;
    while (*(cursor2)) {
        if (*(cursor2) == ',') {
            *cursor1 = *(++cursor2);
            *cursor2 = ' ';
        }
        cursor1++; cursor2++;
    }
    *cursor1 = '\0';
    return atof(deal_bas_r);
}