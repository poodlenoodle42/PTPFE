#pragma once
#include <unistd.h>
#define BUFFER_SIZE (1024*1024)
#define PUNCHING_CONNECTION_ATTEMPTS 10000
#define PUNCHING_WAIT_PER_ATTEMPT_ms 1
#define CONNECTION_IDENTIFIER_LENGTH 30
#define SOCKET_ERROR(val,msg) \
if((val) < 0){\
    fprintf(stderr,msg);\
    exit(1);\
}
#ifndef NDEBUG
#define LOG(msg,...) \
if(args->debug){ \
    printf(msg __VA_OPT__(,) __VA_ARGS__); \
}
#else
#define LOG(msg,...)
#endif


#define YES_NO_QUESTION(msg,ret) \
printf(msg); \
char c;\
scanf(" %c",&c); \
if(c == 'y'){ \
    ret = 1; \
} else { \
    ret = 0;\
}

void strrnd(char * str, size_t len);