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
    
    if(punch(&args->address_info,socket_desc) == -1){
        close(socket_desc);
        return;
    }
    receive_file(args,socket_desc);
    close(socket_desc);
}

void receive_server(const Arguments* args){
    int socket_desc, peer_socket_desc;
    int conn_mode = htonl((uint32_t)Receive);
    char* conn_id = NULL;
    struct sockaddr_in peer_addr;
    SOCKET_ERROR(socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    SOCKET_ERROR(connect(socket_desc,(struct sockaddr*)&args->address_info,sizeof(args->address_info)),"Error connecting\n")

    do{
        printf("Input the connection id\n");
        scanf("%ms",&conn_id);
        if(strlen(conn_id) != CONNECTION_IDENTIFIER_LENGTH){
            printf("The given identifier does not have the right length (%d)\n", CONNECTION_IDENTIFIER_LENGTH);
            free(conn_id);
        }
        else 
            break;
    }while(1);
    SOCKET_ERROR(send(socket_desc,&conn_mode,4,0),"Error sending connection mode\n")
    SOCKET_ERROR(send(socket_desc,conn_id,CONNECTION_IDENTIFIER_LENGTH,0),"Error sending connection identifier\n")
    free(conn_id);
    SOCKET_ERROR(recv(socket_desc,&peer_addr,sizeof(peer_addr),0),"Error receiving peer ip info");

    SOCKET_ERROR(peer_socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating peer socket\n")

    if(punch(&peer_addr,socket_desc) == -1){
        close(peer_socket_desc);
        close(socket_desc);
        return;
    }

    receive_file(args,peer_socket_desc);
    
    close(peer_socket_desc);
    close(socket_desc);
}