#include "map.h"
#include "string.h"
#include "stdlib.h"
Node* new_node(const char* key, Connection_Info* conn_info){
    Node* n = malloc(sizeof(Node));
    n->key = malloc(strlen(key)+1);
    strcpy(n->key,key);
    n->conn_info = *conn_info;
    n->left = NULL;
    n->right = NULL;
    return n;
}
void delete_node(Node* n){
    free(n->key);
    free(n);
}

Node* min_value_node(Node* n){
    Node* node = n;
    while(node && node->left != NULL)
        node = node->left;
    return node;
}

void Add(Map* m, const char* key,Connection_Info* conn_info){
    if(m->root == NULL){
        m->root = new_node(key,conn_info);
        return;
    }
    Node* n = m->root;
    Node* p = n;
    int cmp;
    while(n != NULL){
        p = n;
        cmp = strcmp(key,n->key);
        if(cmp < 0)
            n = n->left;
        else if(cmp > 0)
            n = n->right;
    }
    if(cmp < 0)
        p->left = new_node(key,conn_info);
    else if(cmp > 0)
        p->right = new_node(key,conn_info);
}

int delete_node_from_tree(Node* n, Node* p){
    Node
        if(n == p->left){
        if(n->left == NULL){
            p->left = n->right;
            delete_node(n);
            return 0;
        } else if(n->right == NULL){
            p->left = n->left;
            delete_node(n);
            return 0;
        } else {
            *p->left = *min_value_node(n->right);
            p->left->right = n_restore.right;
            p->left->left = n_restore.left;
            free(n_restore.key);
            return 0;
        }
    } else if(n == p->right){
        if(n->left == NULL){
            p->right = n->right;
            delete_node(n);
            return 0;
        } else if(n->right == NULL){
            p->right = n->left;
            delete_node(n);
            return 0;
        } else {
            *p->right = *min_value_node(n->right);
            p->right->right = n_restore.right;
            p->right->left = n_restore.left;
            free(n_restore.key);
            return 0;
        }
    } else if(n == m->root){
        *m->root = *min_value_node(n->right);
        m->root->right = n_restore.right;
        m->root->left = n_restore.left;
        free(n_restore.key);
    }
}

int Delete(Map* m, const char* key){
    Node* n = m->root;
    Node* p = n;
    int cmp = 1;
    while(cmp != 0){
        cmp = strcmp(key,n->key);
        if(cmp != 0)
            p = n;
        if(cmp < 0)
            n = n->left;
        else if(cmp > 0)
            n = n->right;

        if(n == NULL)
            return -1;
    }
    delete_node_from_tree(n,p);
}

Connection_Info* Lookup(Map* m,const char* key){
    Node* n = m->root;
    int cmp;
    while(cmp != 0){
        cmp = strcmp(key,n->key);
        if(cmp < 0)
            n = n->left;
        else if(cmp > 0)
            n = n->right;
        if(n == NULL)
            return NULL;
    }
    return &n->conn_info;
}

Map* New_Map(){
    Map* m = malloc(sizeof(Map));
    m->root = NULL;
    return m;
}
void delete_tree_rec(Node* n){
    if(n == NULL)
        return;
    delete_tree_rec(n->left);
    delete_tree_rec(n->right);
    delete_node(n);

}
void Delete_Map(Map* m){
    delete_tree_rec(m->root);
    free(m);
}