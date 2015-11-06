#include "decl.h"
#include "stmt.h"
#include "type.h"
#include "expr.h"
#include <stdlib.h>

extern int indent;

struct decl * decl_create( 
        char *name,
        struct type *t,
        struct expr *v,
        struct stmt *c,
        struct decl *next 
    ){
    // create new struct
    struct decl *new_declaration = malloc(sizeof(struct decl));

    new_declaration->name = name;
    new_declaration->type = t;
    new_declaration->value = v;
    new_declaration->code = c;
    new_declaration->next = next;

    return new_declaration;
}

void decl_print( struct decl *d ){
    int i;
    
    if (d != NULL) {
        // print blank space
        for (i=0; i<indent; i++){
            printf("    ");
        }

        // print ident and colon
        printf("%s: ",d->name);

        type_print(d->type);
        if (d->value != 0) {
            printf(" = ");
            expr_print(d->value);
            printf(";\n");
        } else if (d->code != 0) {
            printf(" = {\n");
            stmt_print(d->code);
            printf("}\n");
        } else {
            printf(";\n");
        }

        if (d->next != 0){ 
            decl_print(d->next);
        }
    }
}
