#pragma once
#include <unistd.h>
#define BUFFER_SIZE 0x1000
#define SOCKET_ERROR(val,msg) \
if((val) < 0){\
    fprintf(stderr,msg);\
    exit(1);\
}

