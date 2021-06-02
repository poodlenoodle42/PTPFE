#pragma once
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 0x1000
#define PUNCHING_CONNECTION_ATTEMPTS 5
#define PUNCHING_WAIT_PER_ATTEMPT_ms 100
#define CONNECTION_IDENTIFIER_LENGTH 30
#define MAX_CONNECTIONS 100
#define SOCKET_ERROR(val,msg) \
if((val) < 0){\
    fprintf(stderr,msg);\
    exit(1);\
}
#define SOCKET_ERROR_NO_EXIT(val,msg) \
if((val) < 0){\
    fprintf(stderr,msg);\
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

typedef struct _Connection_Info{
    int sender_socket_desc;
    struct sockaddr_in sender_address_info;
}Connection_Info;