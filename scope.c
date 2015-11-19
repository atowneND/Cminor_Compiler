#include "symbol.h"
#include "hash_table.h"
#include <stdlib.h>

extern int scope_ctr;
struct hash_table *head_HT;

void scope_enter(void){
    // create hash table
    struct hash_table *new_hash_table = hash_table_create(0,0);
    // put at head of list
    head_HT = new_hash_table;
    scope_ctr += 1;
}

void scope_exit(void){
    scope_ctr -= 1;
    // free table?
    // move head to next
}

void scope_bind(const char *name, struct symbol *s){
    if (s==NULL){
        if (name!=NULL){ 
            fprintf(stderr,"Symbol not created properly for %s\n",name);
        }else{
            fprintf(stderr,"No symbol found\n");
        }
        return;
    }
    if (name==NULL){
        if (s!=NULL){ 
            fprintf(stderr,"Unnamed symbol %s\n",s->name);
        }else{
            fprintf(stderr,"No symbol found\n");
        }
        return;
    }

    //printf("%s bound to sym %i %i\n", name, s->kind, s->which);
    printf("%s bound to sym\n", name);
    // add name to hash table
    // with information from s
}

struct symbol *scope_lookup(const char *name){
    struct symbol *s = 0;
//    s = malloc(sizeof(struct symbol));
//    s->kind = SYMBOL_LOCAL;
//    s->which = 3;
//    s->type = 0;
//    s->name = "hello";
    return s;
}

struct symbol *scope_lookup_local(const char *name){
    struct symbol *s = 0;
//    s = malloc(sizeof(struct symbol));
//    s->kind = SYMBOL_LOCAL;
//    s->which = 3;
//    s->type = 0;
//    s->name = "hello";
    return s;
}
