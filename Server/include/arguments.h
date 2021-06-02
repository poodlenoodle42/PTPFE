#pragma once
#include "stdint.h"
typedef enum _Mode {
    Send,Receive
} Mode;
typedef struct _Arguments
{
    uint16_t port;
} Arguments;

Arguments* parse_arguments(int argc, char* argv[]);