#include "receive.h"
#include <sys/socket.h>
#include <stdlib.h>
#include "common.h"
#include "connection.h"
void receive_file(const Arguments* args, int socket){
    char buffer [BUFFER_SIZE];
    int read = 0;
    int read_total = 0;
    int size = 0;
    SOCKET_ERROR(recv(socket,&size,4,0),"Error receiving size\n")
    size = ntohl(size);
    while(read_total < size){
        SOCKET_ERROR(read = recv(socket,buffer,BUFFER_SIZE,0),"Error receiving\n")
        read_total += read;
        fwrite(buffer,1,read,args->file);
    }
}

void receive_direct(const Arguments* args){
    int socket_desc; 

    SOCKET_ERROR(socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    SOCKET_ERROR(connect(socket_desc,(struct sockaddr*)&args->address_info,sizeof(args->address_info)),"Error connecting\n")
    receive_file(args,socket_desc);
    close(socket_desc);
}

void receive_direct_punch(const Arguments* args){
    int socket_desc;
    SOCKET_ERROR(socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    
    while(socket_desc = punch(&args->address_info,socket_desc) == -1){
        fprintf(stderr,"Failed to establish connection, make sure other client is also punching\n");
        int retry;
        YES_NO_QUESTION("Retry [y|n]",retry)
        if(retry == 0)
            exit(0);
    }
    receive_file(args,socket_desc);
}