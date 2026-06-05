#include "crypto.h"
#include <cstring>

void runEncryptionKey(char* content, char* key, unsigned long len){
    for(int i = 0; i < (int)len; i++){
        content[i] = content[i] ^ key[i % strlen(key)];
    }
}