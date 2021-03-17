#include "socket.h"

int InitSocket(){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) return -1;

    // serverAddr 초기화 및 현재 IP와 3000번 포트 사용한다고 알려주기
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET; // Ipv4 방식 사용
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 현재 IP 주소 사용
    addr.sin_port = htons(PORT); // PORT 번호

    // 소켓과 서버의 정보를 묶어준다
    if(bind(sock, (struct sockaddr_in *)&addr, sizeof(addr)) == -1){
        close(sock);
        return -1;
    }

    // MAX_CLIENT_NUM 만큼 연결요청 소켈을 대기하는 연결 대기열을 생성한다
    if(listen(sock, MAX_CLIENT_NUM) == -1){
        close(sock);
        return -1;
    }

    return sock;
}

int ClientAccept(int sock){
    struct sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    int clientSocket = accept(sock, (struct sockaddr_in*)&clientAddr, &clientAddrSize);
    if(clientSocket == -1) return -1;

    char helloMsg[BUF_SIZE] = "안녕하세요.";
    write(clientSocket, helloMsg, sizeof(helloMsg));

    return clientSocket;
}

void sendMsg(int client, char * msg){
    write(client, msg, sizeof(char) * BUF_SIZE);
}

char * receiveMsg(int client){
    char msg[BUF_SIZE];
    read(client, msg, sizeof(char) * BUF_SIZE);
    return msg;
}
