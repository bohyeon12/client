#ifndef SOCKET_H
#define SOCKET_H
#include<stdio.h>
#include <ws2tcpip.h>
#include<winsock2.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 9909
#define ENDSERVER WSACleanup();closesocket(nSocket);nSocket = NULL;

int initiatesocket(void);
void readbuff(char* cursor, char** args, int maxArgs);
void sendandwait(char* message, char* buff, char** args, int buffsize, int argssize);
struct sockaddr_in srv;
static int nSocket;
extern char* user;

#endif