#include "send.h"
#include "common.h"
#include <sys/stat.h>
void send_file(const Arguments* args,int socket){
    char buffer[BUFFER_SIZE];
    struct stat st;
    fstat(fileno(args->file),&st);
    int size = (int)st.st_size;
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
void serve(Arguments* args){
    int server_socket,client_socket;
    SOCKET_ERROR(server_socket = socket(AF_INET,SOCK_STREAM,0),"Error creating socket\n")
    SOCKET_ERROR(bind(server_socket,(struct sockaddr*)args->address_info,sizeof(*args->address_info)),"Error binding socket to addr\n")
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