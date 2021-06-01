#include "connection.h"
#include <stdlib.h>
#include "common.h"
#include <stdio.h>
#include <unistd.h>
int punch(const struct sockaddr_in *target, int socket_desc){

    for(int i = 0; i < PUNCHING_CONNECTION_ATTEMPTS; ++i){
        if(connect(socket_desc,(struct sockaddr*)target,sizeof(*target)) == 0){
            return socket_desc;
        }
        usleep(PUNCHING_WAIT_PER_ATTEMPT_ms);
    }
    return -1;
}