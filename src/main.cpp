#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#include "network.h"
#include "file_io.h"
#include "crypto.h"
#include "util.h"

int main(int argc, const char * argv[]) {
    unsigned long size = 0;
    int pktSize = 0;
    char* buf = nullptr;
    char* fileName;
    char* key;

    if(argc > 1 && strcmp(argv[1], "client")==0){
        char* ip = getIP();
        int port = getPort();

        std::cout << "File to be sent: ";
        fileName = getFileName();
        pktSize = getPacketSize();
        key = getKey();
        std::cout << "\n";

        FILE* file = openFile(fileName);
        size = getFileSize(fileno(file));

        int sockfd = callServer(ip, port);

        write(sockfd, &pktSize, sizeof(int));
        write(sockfd, &size, sizeof(unsigned long));

        buf = (char*) malloc(size);
        fread(buf, 1, size, file);

        runEncryptionKey(buf, key, size);

        sendFile(sockfd, buf, pktSize, size);

        fclose(file);

        free(ip);
    }
    else if(argc > 1 && strcmp(argv[1], "server")==0){
        int port = getPort();

        std::cout << "Save file to: ";
        fileName = getFileName();
        key = getKey();
        std::cout << "\n";

        int sockfd = setupServerSocket(port);
        int connfd = serverSocketAccept(sockfd);

        read(connfd, &pktSize, sizeof(int));
        read(connfd, &size, sizeof(unsigned long));

        buf = (char*) malloc(size);

        recvFile(connfd, buf, pktSize, size);

        runEncryptionKey(buf, key, size);

        FILE *newFile = fopen(fileName, "wb");
        fwrite(buf, sizeof(char), size, newFile);
        fclose(newFile);
    }

    if(argc > 1){
        printMD5(fileName);
        free(buf);
        free(fileName);
        free(key);
    }

    return 0;
}