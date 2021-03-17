#include "header/OrderSystem.h"

int main() {

    // 서버 소켓
    int serverSocket = InitSocket();
    if(serverSocket == -1){
        printf("InitSocket Error\n");
        return 0;
    }

    Client * client = InitClient();

    while(1){
        int clientSocket = ClientAccept(serverSocket);
        if(clientSocket == -1){
            printf("ClientAccept Erron\n");
            break;
        }

        ClientNode * clientNode = InitClientNode(clientSocket);
        pthread_create(&clientNode->thread, NULL, ClientAccess, InitClientParameter(client, clientNode));
        pthread_join(&clientNode->thread, NULL);
    }

    close(serverSocket);
    return 0;
}

