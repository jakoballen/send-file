#include "util.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

char* getIP(){
    std::cout << "Connect to IP address: ";
    char* ip = (char*)calloc(16, sizeof(char));
    scanf("%s", ip);
    return ip;
}

int getPort(){
    int port = 0;
    std::cout << "Port#: ";
    scanf("%d", &port);
    return port;
}

char* getFileName(){
    char* fileName = (char*)calloc(100, sizeof(char));
    scanf("%s", fileName);
    return fileName;
}

int getPacketSize(){
    int pktSize = 0;
    std::cout << "Pkt size: ";
    scanf("%d", &pktSize);
    return pktSize;
}

char* getKey(){
    char* key = (char*)calloc(50, sizeof(char));
    std::cout << "Enter encryption key: ";
    scanf("%s", key);
    return key;
}

void print_hex(const char *string){
    unsigned char *p = (unsigned char *) string;
    printf("%02x%02x...%02x%02x\n",
        p[0], p[1],
        p[strlen(string)-2], p[strlen(string)-1]);
}

void substring(char* s, char* substring, int p, int l){
    int c = 0;
    while(c < l){
        substring[c] = s[p + c - 1];
        c++;
    }
    substring[c] = '\0';
}