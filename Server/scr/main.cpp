extern "C"{
#include "arguments.h"
#include "common.h"
}
#include <search.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "stdio.h"
#include <map>
#include <string>


#define SOCKET_ERROR_CLOSE_AND_CONTINUE(val,msg) \
if((val) == -1){ \
printf(msg); \
close(client_socket_desc); \
continue; \
}

#define SOCKET_ERROR_CLOSE_ALL_AND_CONTINUE(val,msg) \
if((val) == -1){ \
printf(msg); \
close(client_socket_desc); \
close(client_info.sender_socket_desc); \
map.erase(conn_id_s); \
continue; \
}


extern "C"{
int main(int argc, char* argv[]){
    Arguments* args = parse_arguments(argc,argv);
    int server_socket_desc, client_socket_desc;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);
    Connection_Info client_info;
    ENTRY item;
    ENTRY* found_item;
    Mode conn_mode;
    int error;
    char conn_id[CONNECTION_IDENTIFIER_LENGTH];
    std::map<std::string,Connection_Info> map;

    SOCKET_ERROR(server_socket_desc = socket(AF_INET,SOCK_STREAM,0),"Error creating server socket\n")
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = args->port;

    SOCKET_ERROR(bind(server_socket_desc,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in)),"Error binding socket")

    SOCKET_ERROR(listen(server_socket_desc,MAX_CONNECTIONS),"Error listening on server socket\n")

    while(1){
        client_socket_desc = accept(server_socket_desc,(struct sockaddr*)&client_addr,(socklen_t*)&client_addr_size);
        if(client_socket_desc == -1){
            printf("Error accepting connection\n");
        } else {
            SOCKET_ERROR_CLOSE_AND_CONTINUE(recv(client_socket_desc,&conn_mode,4,0),"Error receiving mode\n")
            conn_mode = (Mode)ntohl(conn_mode);
            if(conn_mode == Send){
                SOCKET_ERROR_CLOSE_AND_CONTINUE(recv(client_socket_desc,conn_id,CONNECTION_IDENTIFIER_LENGTH,0),"Error receiving connection identifier\n")
                std::string conn_id_s(conn_id);
                client_info.sender_socket_desc = client_socket_desc;
                client_info.sender_address_info = client_addr;
                map[conn_id_s] = client_info;
            } else if(conn_mode == Receive){
                SOCKET_ERROR_CLOSE_AND_CONTINUE(recv(client_socket_desc,conn_id,CONNECTION_IDENTIFIER_LENGTH,0),"Error receiving connection identifier\n")
                std::string conn_id_s(conn_id);
                int valid;
                if((valid = map.count(conn_id_s)) == 0){
                    SOCKET_ERROR_CLOSE_AND_CONTINUE(send(client_socket_desc,&valid,4,0),"Error sending validity\n")
                    close(client_socket_desc);
                    continue;
                }
                client_info = map[conn_id_s];
                SOCKET_ERROR_CLOSE_ALL_AND_CONTINUE(send(client_socket_desc,&valid,4,0),"Error sending validity\n")
                SOCKET_ERROR_CLOSE_ALL_AND_CONTINUE(send(client_socket_desc,&client_info.sender_address_info,sizeof(struct sockaddr_in),0),"Error sending sender address of sender to receiver\n")
                SOCKET_ERROR_CLOSE_ALL_AND_CONTINUE(send(client_info.sender_socket_desc,&client_addr,sizeof(struct sockaddr_in),0),"Error sending address of receiver to sender\n")
                close(client_socket_desc); 
                close(client_info.sender_socket_desc); 
                map.erase(conn_id_s);
            }
        }
    }


}


}