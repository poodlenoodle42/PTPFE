#include "receive.h"
#include <sys/socket.h>
#include <stdlib.h>
#include "common.h"
void receive(const Arguments* args){
    int socket_desc; 
    char buffer [BUFFER_SIZE];
    int read = 0;
    int read_total = 0;
    int size = 0;
    SOCKET_ERROR(socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    SOCKET_ERROR(connect(socket_desc,(struct sockaddr*)&args->address_info,sizeof(args->address_info)),"Error connecting\n")
    SOCKET_ERROR(recv(socket_desc,&size,4,0),"Error receiving size\n")
    size = ntohl(size);
    while(read_total < size){
        SOCKET_ERROR(read = recv(socket_desc,buffer,BUFFER_SIZE,0),"Error receiving\n")
        read_total += read;
        fwrite(buffer,1,read,args->file);
    }
    close(socket_desc);
}