#include "arguments.h"
#include "map.h"
int main(int argc, char* argv[]){
    Arguments* args = parse_arguments(argc,argv);
    Map* m = New_Map();
    Connection_Info s;
    Add(m,"Hello",&s);
    Add(m,"Moin",&s);
    Add(m,"Heinz",&s);
    Delete(m,"Moin");
    Add(m,"Plump",&s);
    Add(m,"Fp",&s);
    Delete(m,"Hello");
    Delete_Map(m);
}