#ifndef SERVER_ORDERSYSTEM_H
#define SERVER_ORDERSYSTEM_H

#include "RootHeader.h"
#include "Client.h"
#include "socket.h"

// 0 : 로그인 실패, 1 : 로그인 성공
int SignIn(int client, char * userId);

void ClientAccess(ClientParameter * clientParameter);

void orderItem(int client, char * userId);

void showItemList(int client);

#endif //SERVER_ORDERSYSTEM_H
