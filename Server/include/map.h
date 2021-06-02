#pragma once
#include "common.h"


typedef struct _Node{
    struct _Node* right;
    struct _Node* left;
    char* key;
    Connection_Info conn_info;
}Node;

typedef struct _Map{
    Node* root;
}Map;
Map* New_Map();
void Delete_Map(Map* m);
void Add(Map* m, const char* key,Connection_Info* conn_info);
int Delete(Map* m, const char* key);
Connection_Info* Lookup(Map* m,const char* key);