#pragma once                                                                                                                                                                                                                                                                                                                                                                         
#include <stdio.h>                                                                                                                                                                                               
#include <stdlib.h>                                                                                                                                                                                              
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
typedef enum _Mode {
    Send,Receive
} Mode;
typedef struct _Arguments
{
    Mode mode;
    int address;
    int port;
    struct sockaddr_in address_info;
    FILE* file;
} Arguments;

Arguments* parse_arguments(int argc, char* argv[]);