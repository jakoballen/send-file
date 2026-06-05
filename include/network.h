#pragma once

int setupServerSocket(int portno);
int serverSocketAccept(int serverSocket);
int callServer(char *host, int portno);

void sendFile(int sockfd, char* buf, int packetSize, unsigned long fileSize);
void recvFile(int connfd, char* buf, int packetSize, unsigned long fileSize);