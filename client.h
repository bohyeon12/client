#ifndef CLIENT_H
#define CLIENT_H
#include<stdio.h>
#include <ws2tcpip.h>
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 9909
#define ENDSERVER WSACleanup();nSocket = NULL;
void readbuff(char* cursor, char** args, int maxArgs);
void sendandwait(char* message, char* buff, char** args);

struct sockaddr_in srv;
static int nSocket;
static char* user;

int initiatesocket(void);

#endif