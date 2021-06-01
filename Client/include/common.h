#pragma once
#include <unistd.h>
#define BUFFER_SIZE 0x1000
#define PUNCHING_CONNECTION_ATTEMPTS 5
#define PUNCHING_WAIT_PER_ATTEMPT_ms 100
#define CONNECTION_IDENTIFIER_LENGTH 30
#define SOCKET_ERROR(val,msg) \
if((val) < 0){\
    fprintf(stderr,msg);\
    exit(1);\
}

#define YES_NO_QUESTION(msg,ret) \
printf(msg); \
char c;\
scanf("%c",&c); \
if(c == 'y'){ \
    ret = 1; \
} else { \
    ret = 0;\
}

void strrnd(char * str, size_t len);