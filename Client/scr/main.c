#include "arguments.h"
#include <stdlib.h>
#include "receive.h"
#include "send.h"
int main(int argc, char* argv[]){
    Arguments* args =  parse_arguments(argc,argv);
    if(args->mode == Receive){
        receive(args);
    } else if (args->mode == Send){
        serve(args);
    }
    fclose(args->file);
}