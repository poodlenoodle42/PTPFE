#include "arguments.h"
#include <stdlib.h>
#include "receive.h"
#include "send.h"
int main(int argc, char* argv[]){
    Arguments* args =  parse_arguments(argc,argv);
    if(args->mode == Receive && args->direct == 1 && args->punch == 0){
        receive_direct(args);
    } else if (args->mode == Send && args->direct == 1 && args->punch == 0){
        send_direct(args);
    } else if(args->mode == Receive && args->direct == 1 && args->punch == 1){
        receive_direct_punch(args);
    } else if (args->mode == Send && args->direct == 1 && args->punch == 1){
        send_direct_punch(args);
    } else if(args->mode == Receive && args->direct == 0){
        receive_server(args);
    } else if (args->mode == Send && args->direct == 0){
        send_server(args);
    }
    fclose(args->file);
}