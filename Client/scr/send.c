#include "send.h"
#include "common.h"
#include <sys/stat.h>
#include "connection.h"
void send_file(const Arguments* args,int socket){
    char buffer[BUFFER_SIZE];
    struct stat st;
    fstat(fileno(args->file),&st);
    int size = htonl((int)st.st_size);
    SOCKET_ERROR(send(socket,&size,4,0),"Error sending size\n")
    int bytes_read;
    while((bytes_read = fread(buffer,1,BUFFER_SIZE,args->file)) > 0){
        SOCKET_ERROR(send(socket,buffer,bytes_read,0),"Error sending file")
    }

}

int permission_to_send(struct sockaddr_in * addr){
    printf("Accept incoming connection from %s? [y|n] ",inet_ntoa(addr->sin_addr));
    char c;
    scanf("%c",&c);
    if(c == 'y'){
        return 1;
    } else if (c == 'n'){
        return 0;
    } else 
        return permission_to_send(addr);
} 
void send_direct(const Arguments* args){
    int server_socket,client_socket;
    SOCKET_ERROR(server_socket = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    SOCKET_ERROR(bind(server_socket,(struct sockaddr*)&args->address_info,sizeof(args->address_info)),"Error binding socket to addr\n")
    SOCKET_ERROR(listen(server_socket,1),"Listen failed\n")

    //Only one connection
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    SOCKET_ERROR(client_socket = accept(server_socket,(struct sockaddr*)&client_addr,&addr_size),"Accept failed\n")
    if(permission_to_send(&client_addr) == 0){
        return;
    }
    send_file(args,client_socket);
    close(server_socket);
    close(client_socket);
}

void send_direct_punch(const Arguments* args){
    int socket_desc;
    SOCKET_ERROR(socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    
    while(socket_desc = punch(&args->address_info,socket_desc) == -1){
        fprintf(stderr,"Failed to establish connection, make sure other client is also punching\n");
        int retry;
        YES_NO_QUESTION("Retry [y|n]",retry)
        if(retry == 0)
            exit(0);
    }
    send_file(args,socket_desc);
}

void send_server(const Arguments* args){
    int socket_desc, peer_socket_desc;
    int conn_mode = htonl((uint32_t)Send);
    char conn_id[CONNECTION_IDENTIFIER_LENGTH];
    struct sockaddr_in peer_addr,local_addr;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = args->address_info.sin_port;
    SOCKET_ERROR(socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    SOCKET_ERROR(connect(socket_desc,(struct sockaddr*)&args->address_info,sizeof(args->address_info)),"Error connecting\n")


    SOCKET_ERROR(send(socket_desc,&conn_mode,4,0),"Error sending connection mode\n")
    
    
    SOCKET_ERROR(recv(socket_desc,conn_id,CONNECTION_IDENTIFIER_LENGTH,0),"Error receiving connection identifier\n")

    printf("Your connection identifier is %s . give it to your peer to input it\n",conn_id);


    SOCKET_ERROR(recv(socket_desc,&peer_addr,sizeof(peer_addr),0),"Error receiving peer ip info");

    SOCKET_ERROR(peer_socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating peer socket\n")
    SOCKET_ERROR(bind(peer_socket_desc,(struct sockaddr*)&local_addr,sizeof(struct sockaddr_in)),"Error binding peer socket peer socket\n")
    if(punch(&peer_addr,socket_desc) == -1){
        close(peer_socket_desc);
        close(socket_desc);
        return;
    }

    send_file(args,peer_socket_desc);
    
    close(peer_socket_desc);
    close(socket_desc);
}