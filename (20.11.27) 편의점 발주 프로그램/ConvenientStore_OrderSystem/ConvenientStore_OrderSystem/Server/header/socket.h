#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "RootHeader.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 3001
#define MAX_CLIENT_NUM 30


// 소켓 생성 후 소켓 번호 반환
int InitSocket();

int ClientAccept(int sock);

void sendMsg(int client, char * msg);

char * receiveMsg(int client);

#endif //SERVER_SOCKET_H
