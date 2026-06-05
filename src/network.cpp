#include "network.h"
#include "util.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define SA struct sockaddr

int setupServerSocket(int portno){
    struct sockaddr_in servaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        printf("Socket bind failed...\n");
        exit(0);
    }

    if (listen(sockfd, 5) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }

    return sockfd;
}

int serverSocketAccept(int serverSocket){
    struct sockaddr_in cli;
    int len = sizeof(cli);

    int connfd = accept(serverSocket, (struct sockaddr *)(&cli), (socklen_t*)(&len));
    if (connfd < 0) {
        printf("Server accept failed...\n");
        exit(0);
    }

    return connfd;
}

int callServer(char* host, int portno){
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "socket creation failed...\n";
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(host);
    servaddr.sin_port = htons(portno);

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }

    return sockfd;
}

void sendFile(int sockfd, char* buf, int packetSize, unsigned long fileSize){
    size_t totalSent = 0;
    size_t pktNum = 0;
    char* packet = (char*)malloc(sizeof(char)*(packetSize+1));

    while(totalSent < fileSize){
        int sent = write(sockfd, buf + totalSent, packetSize);

        if(pktNum < 2 || pktNum > ((size_t)fileSize/packetSize)-2){
            substring(buf, packet, totalSent, packetSize);
            printf("Sent packet #%zu - encrypted as ", pktNum);
            print_hex(packet);
        }

        if(pktNum == 2){
            printf("\t\t\t.\n\t\t\t.\n\t\t\t.\n\t\t\t.\n");
        }

        totalSent += sent;
        pktNum++;
    }

    std::cout << "Send success!\n";
}

void recvFile(int connfd, char* buf, int packetSize, unsigned long fileSize){
    size_t totalRecvd = 0;
    char* packet = (char*)malloc(sizeof(char)*(packetSize+1));
    int recvd = 0;
    size_t pktNum = 0;

    while(totalRecvd < fileSize){
        recvd = recv(connfd, buf + totalRecvd, packetSize, 0);

        if(pktNum < 2 || pktNum > ((size_t)fileSize/packetSize)-2){
            substring(buf, packet, totalRecvd, packetSize);
            printf("Rec packet #%zu - encrypted as ", pktNum);
            print_hex(packet);
        }

        if(pktNum == 2){
            printf("\t\t\t.\n\t\t\t.\n\t\t\t.\n\t\t\t.\n");
        }

        pktNum++;
        totalRecvd += recvd;
    }

    printf("Receive success!\n");
}