#include"client.h"

int initiatesocket() {
    int nRet = 0;
    WSADATA ws;

    // Initialize Winsock
    if ((nRet = WSAStartup(MAKEWORD(2, 2), &ws)) != 0) {
        printf("WSA failed to initialize: %d\n", nRet);
        ENDSERVER
        return 1;
    }
    printf("WSA initialized successfully\n");

    // Initialize socket
    nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket == INVALID_SOCKET) {
        printf("The socket not opened, error: %d\n", WSAGetLastError());
        ENDSERVER
        return 1;
    }
    printf("The socket opened successfully\n");

    // Set up the sockaddr_in structure
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &srv.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        closesocket(nSocket);
        
        return 1;
    }
    memset(&(srv.sin_zero), 0, 8);

    // Connect to the server
    nRet = connect(nSocket, (struct sockaddr*)&srv, sizeof(srv));
    if (nRet == SOCKET_ERROR) {
        printf("Failed to connect to the server, error: %d\n", WSAGetLastError());
        closesocket(nSocket);
        ENDSERVER
        return 1;
    }
    printf("Successfully connected to the server\n");

    return 0;
}

void readbuff(char* buff, char** args, int maxArgs) {
    int start = 0, end = 0, i = 0;

    while (buff[end] != '\0') {
        if (buff[end] == ',') {
            buff[end] = '\0';  // Null-terminate the current token
            if (i < maxArgs) {
                args[i++] = buff + start;
            }
            start = end + 1;
        }
        end++;
    }

    // Add the last token
    if (i < maxArgs) {
        args[i++] = buff + start;
    }

    // Ensure the remaining pointers in args are NULL
    while (i < maxArgs) {
        args[i++] = NULL;
    }
}

void sendandwait(char* message, char* buff, char** args) {
    send(nSocket, message, strlen(message), 0);
    Sleep(2000);
    recv(nSocket, buff, sizeof(buff), 0);
    readbuff(buff + 3, args,sizeof(args)/sizeof(char*));
}