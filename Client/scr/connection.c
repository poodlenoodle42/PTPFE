#include "connection.h"
#include <stdlib.h>
#include "common.h"
#include <stdio.h>
#include <unistd.h>
int punch_make_connection(const struct sockaddr_in *target, int socket_desc){

    for(int i = 0; i < PUNCHING_CONNECTION_ATTEMPTS; ++i){
        if(connect(socket_desc,(struct sockaddr*)target,sizeof(*target)) == 0){
            return 0;
        }
        usleep(PUNCHING_WAIT_PER_ATTEMPT_ms*1000);
    }
    return -1;
}
int punch(const struct sockaddr_in *target, int socket_desc){
    while(punch_make_connection(target,socket_desc) == -1){
        fprintf(stderr,"Failed to establish connection, make sure other client is also punching\n");
        int retry;
        YES_NO_QUESTION("Retry [y|n]",retry)
        if(retry == 0)
            return -1;
    }
    return 0;
}