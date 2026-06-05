#pragma once
#include <cstdio>

FILE* openFile(char* fileName);
unsigned long getFileSize(int fd);
void printMD5(char* fileName);