#include "Client.h"

ClientNode * InitClientNode(int sock){
    ClientNode * node = (ClientNode *)malloc(sizeof(ClientNode));
    node->nextNode = node->preNode = NULL;
    node->sock = sock;
    return node;
}

Client * InitClient(){
    Client * client = (Client *)malloc(sizeof(Client));
    client->front = client->back = NULL;
    client->size = 0;
    return client;
}

ClientParameter * InitClientParameter(Client * client, ClientNode * clientNode){
    addClient(client, clientNode);
    ClientParameter * parameter = (ClientParameter *)malloc(sizeof(ClientParameter));
    parameter->client = client;
    parameter->clientNode = clientNode;
    return parameter;
}

int addClient(Client * client, ClientNode * node){
    if(client == NULL || node == NULL) return 0;
    if(client->front == NULL){
        client->front = client->back = node;
    }else{
        client->back->nextNode = node;
        node->preNode = client->back;
        client->back = node;
    }
    client->size++;
    return 1;
}

int removeClient(Client * client, int sock){
    if(client == NULL || sock == -1) return 0;
    for(ClientNode * node = client->front; node != NULL; node = node->nextNode){
        if(node->sock == sock){
            if(node->preNode != NULL){
                node->preNode->nextNode = node->nextNode;
            }
            if(node->nextNode != NULL){
                node->nextNode->preNode = node->preNode;
            }
            if(client->front == node){
                client->front = node->nextNode;
            }
            if(client->back == node){
                client->back = node->preNode;
            }
            client->size--;
            free(node);
            return 1;
        }
    }
    return 0;
}