#include "decl.h"
#include <stdlib.h>

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *c, struct decl *next ){
    struct decl *new_declaration = malloc(sizeof(struct decl *));
    new_declaration->name = name;
    new_declaration->type = t;
    new_declaration->value = v;
    new_declaration->code = c;
    new_declaration->next = next;

    return new_declaration;
}

void decl_print( struct decl *d, int indent ){
}
