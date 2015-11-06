#include "decl.h"
#include "stmt.h"
#include "type.h"
#include "expr.h"
#include <stdlib.h>

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *c, struct decl *next ){
    // create new struct
    struct decl *ptr_new_declaration = malloc(sizeof(struct decl *));
    struct decl new_declaration;
    ptr_new_declaration = &new_declaration;

    new_declaration.name = name;
    new_declaration.type = t;
    new_declaration.value = v;
    new_declaration.code = c;
    new_declaration.symbol = 0;
    new_declaration.next = next;
    
    decl_print(ptr_new_declaration, 0);
    return ptr_new_declaration;
}

void decl_print( struct decl *d, int indent ){
    int i;
    
    // print blank space
    for (i=0; i<indent; i++){
        printf("\t");
    }

    // print ident and colon
    printf("%s, %p: ",d->name, &(d->name));

    type_print(d->type);
    if (d->value != 0) {
        printf(" = ");
        expr_print(d->value);
        printf(";\n");
    } else if (d->code != 0) {
        printf(" = {\n");
        stmt_print(d->code, indent + 1);
        for (i=0; i<indent; i++){
            printf("\t");
        }
        printf("}");
    } else {
        printf(";\n");
    }

    indent = indent + 1;
    if (d->next != 0){ 
        decl_print(d->next, indent);
    }
}
