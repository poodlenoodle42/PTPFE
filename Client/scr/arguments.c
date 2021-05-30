#include "arguments.h"
#include <getopt.h>    
#include <string.h>
Arguments* parse_arguments(int argc, char* argv[]){
    Arguments* args = malloc(sizeof(args));
    args->address_info = malloc(sizeof(struct sockaddr_in));
    memset(args->address_info,0,sizeof(struct sockaddr_in));
    args->address_info->sin_family = AF_INET;
    int c;
    char * file_name;
    while ((c = getopt (argc, argv, "alpf:")) != -1){
        switch (c)
        {
        case 'a':
            args->address = 1;
            args->address_info->sin_addr.s_addr = inet_addr(optarg);
            break;
        case 'l':
            args->listen_send = 1;
            break;
        case 'p':
            args->port = 1;
            args->address_info->sin_port = htonl(atoi(optarg));
            break;
        case 'f':
            file_name = strdup(optarg);
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
    if(args->listen_send = 1)
        args->file = fopen(file_name,"w");
    else 
        args->file = fopen(file_name,"r");
    free(file_name);
    return args;
}