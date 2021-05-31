#include "arguments.h"
#include <stdlib.h>
int main(int argc, char* argv[]){
    Arguments* args =  parse_arguments(argc,argv);
    
    fclose(args->file);
    free(args->address_info);
    free(args);
}