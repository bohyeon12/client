#pragma once
#include<stdio.h>
#include<winsock2.h>
#define PORT 9909
#define ENDSERVER WSACleanup();return(EXIT_FAILURE);

struct sockaddr_in srv;
static int nSocket;

int initiatesocket()