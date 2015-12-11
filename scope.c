#include "hash_table.h"
#include "type.h"
#include "reg.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
extern int scope_ctr;
extern int param_ctr;
extern int string_counter;
struct type;


struct hash_table_node{
    struct hash_table *current_hash_table;
    struct hash_table_node *next_hash_table;
};

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

struct symbol {
	symbol_t kind;
	int which;
	struct type *type;
	char *name;
	struct expr *expr;
	struct hash_table_node *function_hash_table;
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
    param_ctr = 0;
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
//    hash_table_clear(head_hash_table_node->current_hash_table);
    head_hash_table_node = head_hash_table_node->next_hash_table;
    scope_ctr -= 1;
    param_ctr = 0;
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
            printf("%s bound to sym GLOBAL %s\n", name, s->name);
            break;
    }
}

struct symbol *scope_lookup(const char *name){
    struct symbol *sym = hash_table_lookup(head_hash_table_node->current_hash_table,name);
    struct hash_table_node *tmp = head_hash_table_node->next_hash_table;
    while ((!sym) && (tmp != NULL)){
        sym = hash_table_lookup(tmp->current_hash_table, name);
        tmp = tmp->next_hash_table;
    }

    return sym;
}

struct symbol *scope_lookup_function(const char *name, struct hash_table_node *ht){
    struct symbol *sym = hash_table_lookup(ht->current_hash_table,name);
    struct hash_table_node *tmp = ht->next_hash_table;
    while ((!sym) && (tmp != NULL)){
        sym = hash_table_lookup(tmp->current_hash_table, name);
        tmp = tmp->next_hash_table;
    }

    return sym;
}

struct symbol *scope_lookup_local(const char *name){
    struct symbol *sym = hash_table_lookup(head_hash_table_node->current_hash_table, name);

    return sym;
}

struct symbol *symbol_create(
        symbol_t kind,
        struct type *type,
        char *name,
        void *value
){
    struct symbol *sym = malloc(sizeof(struct symbol));
    int symbol_number = hash_table_size(head_hash_table_node->current_hash_table);
    sym->which = symbol_number - param_ctr;
    sym->kind = kind;
    sym->type = type;
    sym->name = name;
    sym->expr = value;

    return sym;
}

char *symbol_code(struct symbol *s, FILE *fd){
    // this needs work
    // TODO symbol_code - EVERYTHING BREAKS
    if (!s) return "";
    char *str = malloc(sizeof(char)*256);
    if (s->kind == SYMBOL_PARAM){
        int offset = 8*(s->which + 1);
        sprintf(str,"-%i(%%rbp)",offset);
        //fprintf(fd,"mov %s, -%i(%%rbp)",register_name(e->reg),sizeof(arg0))
        //fprintf(fd,"mov -%i(%%rbp), %s",register_name(e->reg),sizeof(arg0))
    } else {
        switch (s->type->kind){
            case TYPE_BOOLEAN:
                // definitely broken
                if (s->expr->literal_value == 0){
                    strcpy(str,"false");
                } else if (s->expr->literal_value == 1){
                    strcpy(str,"true");
                } else {
                    fprintf(stderr,"Improper boolean literal value\n");
                }
                break;
            case TYPE_CHARACTER:
                // should work
                sprintf(str,"$%i",s->expr->literal_value);
                break;
            case TYPE_INTEGER:
                // should kind of work
                sprintf(str,"%s",register_name(s->expr->reg));
                break;
            case TYPE_STRING:
                // TODO cannot test until print works
                fprintf(fd,"    lea STR%i, %s\n",string_counter-1,register_name(s->expr->reg));
                sprintf(str,"%s",register_name(s->expr->reg));
                break;
            case TYPE_ARRAY:
                // should kind of work
                fprintf(stderr,"Arrays not supported: cannot print array literal\n");
                strcpy(str,"");
                break;
            case TYPE_FUNCTION:
                // who knows
//                strcpy(str,"%rax");
                break;
            case TYPE_VOID:
                // who knows
                fprintf(stderr,"VOID: scope.c:159 nothing should be moved\n");
                strcpy(str,"0");
                break;
        }
    }
    return str;
}
