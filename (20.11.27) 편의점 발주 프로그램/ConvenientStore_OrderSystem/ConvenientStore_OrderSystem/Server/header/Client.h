#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "RootHeader.h"
#include <pthread.h>

typedef struct  ClientNode{
    int sock;
    char id[BUF_SIZE];
    char name[BUF_SIZE];
    pthread_t thread;
    struct ClientNode * nextNode;
    struct ClientNode * preNode;
}ClientNode;

typedef struct Client{
    int size;
    ClientNode * front;
    ClientNode * back;
}Client;

typedef struct ClientParameter{
    ClientNode * clientNode;
    Client * client;
}ClientParameter;

ClientNode * InitClientNode(int sock);

Client * InitClient();

ClientParameter * InitClientParameter(Client * client, ClientNode * clientNode);

// 0 : Client 추가 실패, 1 : Client 추가 성공
int addClient(Client * client, ClientNode * node);

// 0 : Client 제거 실패, 1 : Client 제거 성공
int removeClient(Client * client, int sock);


#endif //SERVER_CLIENT_H
