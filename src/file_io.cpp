#include "file_io.h"

#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

FILE* openFile(char* fileName){
    FILE* file = fopen(fileName, "rb");
    if(!file){
        std::cout << "Error while reading the file.\n";
    }
    return file;
}

unsigned long getFileSize(int fd){
    struct stat stat_buf;
    int rc = fstat(fd, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void printMD5(char* fileName){
    char* cmd = (char*) calloc(strlen(fileName)+7+1, sizeof(char));
    strcpy(cmd, "md5sum ");
    strcat(cmd, fileName);
    system(cmd);
    free(cmd);
}