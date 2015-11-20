#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

struct a {
    struct a *next;
    int x;
};

int main(){
    struct a *foo = malloc(sizeof(struct a));
    struct a *bar = malloc(sizeof(struct a));
    foo->x = 3;
    foo->next = bar;

//    struct hash_table *h;
//    if (!h) hash_table_firstkey(h);
//    h = hash_table_create(0,0);
//
//    char *filename = "bar";
//    FILE *file = fopen(filename,"r");
//
//    hash_table_insert(h,filename,file);
//    hash_table_insert(h,"hello_world",file);
//
//    hash_table_firstkey(h);
//
//    char *key;
//    void *value;
//    while (hash_table_nextkey(h,&key,&value)){
//        printf("%s\n",key);
//    }
//
    return 0;
}

