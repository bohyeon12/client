#include <stdio.h>
#include "registerLogin.h"
#include "mainspace.h"
#include "socket.h"

char* user = NULL;
int main() {

    int menuNum = 0;
    while (1) {
        if (user == NULL) {
            printf("1: Login   2: Sign up 3. Exit\n");
            scanf_s("%d", &menuNum);
            if (menuNum == 1) {
                login();            }
            else if (menuNum == 2) {
                createAccount();
            }
            else if (menuNum == 3) {
                exit(0);
            }
            else {
                printf("Wrong input. Try again\n");
            }
        }
        else {
            printf("1. Input account informations\n");
            printf("2. View account\n");
            printf("3. Delete account\n");
            printf("4. Get percentile of your asset to same age group\n");
            printf("5. Log out\n");
            printf("Put a service number you want: ");
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
                printf("Wrong input. Try again\n");
            }
        }
        
    }
    return 0;
}