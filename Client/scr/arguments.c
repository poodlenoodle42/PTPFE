#include "arguments.h"
#include <getopt.h>    
#include <string.h>
#include <stdlib.h>
void check_arg(Arguments* args);

Arguments* parse_arguments(int argc, char* argv[]){
    static Arguments args;
    int c;
    char * file_name = NULL;
    memset(&args,0,sizeof(Arguments));
    args.address_info.sin_family = AF_INET;

    opterr = 0;

    const static struct option long_options[] = {
        {"address", required_argument, 0, 'a'},
        {"receive", no_argument,0,'r'},
        {"send", no_argument, 0, 's'},
        {"port", required_argument, 0, 'p'},
        {"file", required_argument, 0,'f'},
        {"direct", no_argument, &args.direct,1},
        {"punch",no_argument,&args.punch, 1},
        {"debug",no_argument,&args.debug,1},
        {0,0,0,0}
    };
    int option_index;
    while ((c = getopt_long(argc, argv, "a:rsp:f:d", long_options,&option_index)) != -1){
        switch (c)
        {
        case 'a':
            args.address = 1;
            args.address_info.sin_addr.s_addr = inet_addr(optarg); 
            break;
        case 'r':
            args.mode = Receive;
            break;
        case 's':
            args.mode = Send;
            break;
        case 'p':
            args.port = 1;
            args.address_info.sin_port = htons((uint16_t)atoi(optarg));
            break;
        case 'f':
            int len = strlen(optarg);
            file_name = malloc(len+1);
            strcpy(file_name,optarg);
            break;
        case 'd':
            args.direct = 1;
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
    if(args.mode == Receive && file_name != NULL)
        args.file = fopen(file_name,"w");
    else if(args.mode == Send && file_name != NULL)
        args.file = fopen(file_name,"r");
    check_arg(&args);
    free(file_name);
    return &args;
}

void check_arg(Arguments* args){
    if(args->mode == Send && args->port == 0 && args->direct == 1){
        if(args->punch == 1 && args->address == 0){
            fprintf(stderr,"Port and address must be specified for punching\n");
            exit(1);
        }
        fprintf(stderr,"Port must be specified in send mode\n");
        exit(1);
    } else if(args->mode == Receive && args->direct == 1 && (args->address == 0 || args->port == 0)){
        fprintf(stderr,"Port and address must be specified in receive mode\n");
        exit(1);
    } else if(args->direct == 0 && (args->address == 0 || args->port == 0)){
        fprintf(stderr,"When using server, address and port of the server must be specified\n");
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
    if(args->file == NULL){
        fprintf(stderr,"File must be specified\n");
        exit(1);
    } else if(ferror(args->file)){
        fprintf(stderr,"Error opening file\n");
        exit(1);
    }

}

