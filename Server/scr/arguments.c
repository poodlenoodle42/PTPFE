#include "arguments.h"
#include <getopt.h>    
#include <string.h>
#include <stdlib.h>
void check_arg(Arguments* args);

Arguments* parse_arguments(int argc, char* argv[]){
    static Arguments args;
    opterr = 0;
    int c;
    const static struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {0,0,0,0}
    };
    int option_index;
    while ((c = getopt_long(argc, argv, "p:", long_options,&option_index)) != -1){
        switch (c)
        {
        case 'p':
            args.port = htons((uint16_t)atoi(optarg));
            break;
        default:
            break;
        }
    }
    return &args;
}


