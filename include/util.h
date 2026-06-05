#pragma once

char* getIP();
int getPort();
char* getFileName();
int getPacketSize();
char* getKey();

void print_hex(const char *string);
void substring(char* s, char* substring, int p, int l);