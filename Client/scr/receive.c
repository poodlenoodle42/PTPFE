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
    if((socket_desc = socket(AF_INET,SOCK_STREAM,0)) == -1){
        fprintf(stderr,"Error creating socket\n");
        exit(1);
    }
    if(connect(socket_desc,(struct sockaddr*)args->address_info,sizeof(*(args->address_info))) == -1){
        fprintf(stderr,"Error connecting\n");
        exit(1);
    }
    int r = recv(socket_desc,&size,4,0);
    if(r == -1){
        fprintf(stderr,"Error receiving size\n");
        exit(1);
    }
    size = ntohl(size);
    while(read_total < size){
        if((read = recv(socket_desc,buffer,BUFFER_SIZE,0)) < 0){
            fprintf(stderr,"Error receiving\n");
            exit(1);
        }
        read_total += read;
        fwrite(buffer,1,read,args->file);
    }
}