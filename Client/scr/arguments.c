#include "arguments.h"
#include <getopt.h>    
#include <string.h>
#include <stdlib.h>
void check_arg(Arguments* args);

Arguments* parse_arguments(int argc, char* argv[]){
    Arguments* args = malloc(sizeof(Arguments));
    memset(args,0,sizeof(Arguments));
    args->address_info.sin_family = AF_INET;
    int c;
    char * file_name;
    opterr = 0;
    while ((c = getopt (argc, argv, "a:rsp:f:")) != -1){
        switch (c)
        {
        case 'a':
            args->address = 1;
            args->address_info.sin_addr.s_addr = inet_addr(optarg); 
            break;
        case 'r':
            args->mode = Receive;
            break;
        case 's':
            args->mode = Send;
            break;
        case 'p':
            args->port = 1;
            args->address_info.sin_port = htons((uint16_t)atoi(optarg));
            break;
        case 'f':
            int len = strlen(optarg);
            file_name = malloc(len+1);
            strcpy(file_name,optarg);
            break;
        case '?':
            if (optopt == 'a' || optopt == 'p' || optopt == 'f')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else
                fprintf (stderr, "Option -%c not known.\n", optopt);
        default:
            break;
        }
    }
    if(args->mode == Receive)
        args->file = fopen(file_name,"w");
    else 
        args->file = fopen(file_name,"r");
    check_arg(args);
    free(file_name);
    return args;
}

void check_arg(Arguments* args){
    if(args->mode == Send && args->port == 0){
        fprintf(stderr,"Port must be specified in send mode");
    } else if(args->mode == Receive && (args->address == 0 || args->port == 0)){
        fprintf(stderr,"Port and address must be specified in receive mode");
        exit(1);
    }
    if(args->address_info.sin_addr.s_addr == (in_addr_t)-1 && args->address == 1){
        fprintf(stderr,"Invalid ip address notation\n");
        exit(1);
    }
    if(args->address_info.sin_port == 0 && args->port){
        fprintf(stderr,"Invalid port notation\n");
        exit(1);
    }
    if(ferror(args->file)){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }

}