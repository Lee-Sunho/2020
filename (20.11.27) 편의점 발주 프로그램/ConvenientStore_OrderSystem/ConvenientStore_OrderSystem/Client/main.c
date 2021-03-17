#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
#define SERVER_IP "127.0.0.1"
#define PORT 3001

// -1 : 프로그램 종료, 0 : 로그인 실패, 1 : 로그인 성공
int SignIn(int client);

void Menu();

// message 보내기
void sendMsg(int client, char * msg);

// message 받기
char * receiveMsg(int client);

void orderItem(int client);

void showItemList(int client);

void showOrderList(int client);

int main() {

    // 소켓 생성
    int clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1){
        printf("main -> socket() error\n");
        return 0;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1){
        printf("main -> connect() error\n");
        return 0;
    }

    printf("%s\n", receiveMsg(clientSocket));

    while(1){
        int ret = SignIn(clientSocket);
        if(ret == -1){
            close(clientSocket);
            return 0;
        }
        if(ret) break;
    }

    while(1){
        Menu();
        int command; scanf("%d", &command);
        char msg[BUF_SIZE];
        switch(command){
            case 1:
                sendMsg(clientSocket, "1");
                close(clientSocket);
                return 0;
            case 2:
                sendMsg(clientSocket, "2");
                orderItem(clientSocket);
                break;
            case 3:
                sendMsg(clientSocket, "3");
                showItemList(clientSocket);
                break;
            case 4:
                sendMsg(clientSocket, "4");
                showOrderList(clientSocket);
                break;
            default:
                printf("잘못된 입력입니다. 다시 입력해 주십시오\n");
        }
    }
}


int SignIn(int client){
    // 사용자에게 입력받을 유저 정보 저장
    char userId[BUF_SIZE];
    char userPwd[BUF_SIZE];

    printf("아이디 : "); scanf("%s", userId);
    printf("비밀번호 : "); scanf("%s", userPwd);

    sendMsg(client, userId);
    sendMsg(client, userPwd);

    // 로그인 결과 저장
    char * ret = receiveMsg(client);
    if(!strcmp(ret, "exit")){
        printf("프로그램을 종료합니다.\n");
        return -1;
    }else if(!strcmp(ret, "fail")){
        printf("로그인 정보가 맞지 않습니다. 다시 로그인 해주십시오\n");
        return 0;
    }else{
        printf("%s\n", ret);
        return 1;
    }
}

void Menu(){
    printf("-------------\n");
    printf("1.프로그램 종료\n");
    printf("2.상품 발주\n");
    printf("3.발주 가능 상품 내역\n");
    printf("4.최근 발주 내역\n");
    printf("-------------\n");
    printf("(번호로 입력해 주시기 바랍니다)\n");
}

void orderItem(int client){
    int orderItemNum, orderItemCnt;
    printf("발주할 상품의 번호를 입력해 주십시오 : ");
    scanf("%d", &orderItemNum);
    printf("상품의 개수를 입력해 주십시오(1 ~ 100) : ");
    scanf("%d", &orderItemCnt);
    if(1 > orderItemCnt || 100 < orderItemCnt){
        printf("개수를 잘못 입력하셨습니다\n");
        return;
    }

    char tmp1[BUF_SIZE], tmp2[BUF_SIZE];
    sprintf(tmp1, "%d", orderItemNum);
    sendMsg(client, tmp1);

    sprintf(tmp2, "%d", orderItemCnt);
    sendMsg(client, tmp2);

    printf("%s\n", receiveMsg(client));
}

void showItemList(int client){
    int itemNum = atoi(receiveMsg(client));
    printf("총 상품 개수 : %d\n", itemNum);
    for(int i=1; i<=itemNum; i++) {
        printf("%d. %s\n", i, receiveMsg(client));
    }
}

void showOrderList(int client){
    int listNum = atoi(receiveMsg(client));
    printf("상품 발주 수 : %d\n", listNum);
    for(int i=1; i<=listNum; i++){
        printf("%d. %s\n", i, receiveMsg(client));
    }
}

void sendMsg(int client, char * msg){
    write(client, msg, sizeof(char) * BUF_SIZE);
}

char * receiveMsg(int client){
    char recMsg[BUF_SIZE];
    read(client, recMsg, sizeof(char) * BUF_SIZE);
    return recMsg;
}