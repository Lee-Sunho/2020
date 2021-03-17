#include "OrderSystem.h"

int SignIn(int client, char * userId){
    // 사용자에게 입력받을 유저 정보를 저장
    char userPwd[BUF_SIZE];

    read(client, userId, sizeof(char) * BUF_SIZE);
    read(client, userPwd, sizeof(char) * BUF_SIZE);

    FILE * userFile = fopen("resources/User.txt", "r");

    // 서버에 저장된 사용자 유저 정보를 저장
    char name[BUF_SIZE];
    char id[BUF_SIZE];
    char pwd[BUF_SIZE];
    char msg[BUF_SIZE] = "fail";

    int ret = 0;

    while(!feof(userFile)){
        fscanf(userFile, "%s %s %s", name, id, pwd);
        if(!strcmp(userId, id)){
            if(!strcmp(userPwd, pwd)){
                sprintf(msg, "%s님 환영합니다", name);
                ret = 1;
            }
            break;
        }
    }

    write(client, msg, sizeof(char) * BUF_SIZE);
    fclose(userFile);
    return ret;
}

void orderItem(int client, char * userId){
    char orderItemNum[BUF_SIZE];
    read(client, orderItemNum, sizeof(char) * BUF_SIZE);
    char orderItemCnt[BUF_SIZE];
    read(client, orderItemCnt, sizeof(char) * BUF_SIZE);

    FILE * itemList = fopen("resources/ItemList.txt", "r");

    int itemCnt;
    fscanf(itemList, "%d", &itemCnt);

    if(1 > atoi(orderItemNum) || itemCnt < atoi(orderItemNum)){
        sendMsg(client, "올바르지 않은 상품 번호입니다\n");
        return;
    }

    itemCnt = atoi(orderItemNum);
    char item[BUF_SIZE];
    char price[BUF_SIZE];

    while(itemCnt--){
        fscanf(itemList, "%s %s", item, price);
    }
    fclose(itemList);

    char msg[BUF_SIZE];
    sprintf(msg, "%s %s개 발주 성공", item, orderItemCnt);

    sendMsg(client, msg);

    FILE * orderList = fopen("resources/OrderList.txt", "a");
    fprintf(orderList, "%s %s %s %s\n", getCurTime(), userId, item, orderItemCnt);
    fclose(orderList);

}

void showItemList(int client){
    FILE * itemList = fopen("resources/ItemList.txt", "r");

    char itemNum[BUF_SIZE];
    fscanf(itemList, "%s", itemNum);
    sendMsg(client, itemNum);

    while(!feof(itemList)){
        char item[BUF_SIZE];
        char price[BUF_SIZE];
        fscanf(itemList, "%s %s", item, price);
        sprintf(item, "%s %s원",item, price);
        sendMsg(client, item);
    }

    fclose(itemList);
}

void showOrderList(int client, char * userId){
    FILE * orderList = fopen("resources/OrderList.txt", "r");

    int listNum = 0;
    char orderDate[BUF_SIZE];
    char orderTime[BUF_SIZE];
    char orderId[BUF_SIZE];
    char item[BUF_SIZE];
    char itemNum[BUF_SIZE];

    while(!feof(orderList)){
        fscanf(orderList, "%s %s %s %s %s", orderDate, orderTime, orderId, item, itemNum);
        if(!strcmp(orderId, userId)) listNum++;
    }

    char msg[BUF_SIZE];
    sprintf(msg, "%d", listNum);
    sendMsg(client, msg);
    fclose(orderList);

    orderList = fopen("resources/OrderList.txt", "r");

    while(!feof(orderList)){
        fscanf(orderList, "%s %s %s %s %s", orderDate, orderTime, orderId, item, itemNum);
        sprintf(msg, "%s %s %s %s", orderDate, orderTime, item, itemNum);
        if(!strcmp(orderId, userId)){
            sendMsg(client, msg);
        }
    }
    fclose(orderList);
}

void ClientAccess(ClientParameter * clientParameter){
    int sock = clientParameter->clientNode->sock;
    char userId[BUF_SIZE]="";
    while(!SignIn(sock, userId));

    while(1){
        char recMsg[BUF_SIZE];
        read(sock, recMsg, sizeof(char) * BUF_SIZE);
        if(!strcmp(recMsg, "1")) break;
        else if(!strcmp(recMsg, "2")){
            orderItem(sock, userId);
        }else if(!strcmp(recMsg, "3")){
            showItemList(sock);
        }else if(!strcmp(recMsg, "4")){
            showOrderList(sock, userId);
        }
    }

    close(sock);
    removeClient(clientParameter->client, sock);
}
