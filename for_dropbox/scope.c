#include "symbol.h"
#include "hash_table.h"
#include <string.h>
#include <stdlib.h>

struct hash_table_node{
    struct hash_table *current_hash_table;
    struct hash_table_node *next_hash_table;
};

extern int scope_ctr;

struct hash_table_node *head_hash_table_node;

void sym_table_print(struct hash_table *h){
    printf("scope = %i:\n\t",scope_ctr);
    char *key;
    void *value;
    hash_table_firstkey(h);
    while(hash_table_nextkey(h,&key,&value)){
        printf("table contains: %s\n\t",key);
    }
}

void scope_enter(void){
    struct hash_table_node *htp = malloc(sizeof(struct hash_table_node));

    // create hash table
    htp->current_hash_table = hash_table_create(0,0);

    // put at head of list
    if (head_hash_table_node == NULL){
        htp->next_hash_table = NULL;
    } else {
        htp->next_hash_table = head_hash_table_node;
    }
    head_hash_table_node = htp;

    scope_ctr += 1;
}

void scope_exit(void){
    // move head to next
    hash_table_clear(head_hash_table_node->current_hash_table);
    head_hash_table_node = head_hash_table_node->next_hash_table;
    scope_ctr -= 1;
}

void scope_bind(const char *name, struct symbol *s){
    // add name to hash table
    hash_table_insert(head_hash_table_node->current_hash_table,name,s);

    switch (s->kind) {
        case SYMBOL_LOCAL:
            printf("%s bound to sym LOCAL %i\n", name, s->which);
            break;
        case SYMBOL_PARAM:
            printf("%s bound to sym PARAM %i\n", name, s->which);
            break;
        case SYMBOL_GLOBAL:
            printf("%s bound to sym GLOBAL %i\n", name, s->which);
            break;
    }
//    sym_table_print(head_hash_table_node->current_hash_table);
}

struct symbol *scope_lookup(const char *name){
    struct symbol *sym = hash_table_lookup(head_hash_table_node->current_hash_table,name);
    struct hash_table_node *tmp = head_hash_table_node;
    if ((!sym) && (scope_ctr>0)){
        tmp = tmp->next_hash_table;
        sym = hash_table_lookup(tmp->current_hash_table, name);
    }

    return sym;
}

struct symbol *scope_lookup_local(const char *name){
    struct symbol *sym = hash_table_lookup(head_hash_table_node->current_hash_table, name);

    return sym;
}
