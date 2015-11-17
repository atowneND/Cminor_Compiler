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
    if (d != NULL) {
        // print ident and colon
        printf("%s: ",d->name);

        type_print(d->type);
        if (d->value != 0) {
            printf(" = ");
            if (d->value->next != NULL) {
                printf("{");
            }
            expr_print(d->value);
            if (d->value->next != NULL) {
                printf("}");
            }
            printf(";\n");
        } else if (d->code != 0) {
            printf(" = {\n");
            indent += 1;
            stmt_print(d->code);
            indent -= 1;
            printf("}\n");
        } else {
            printf(";\n");
        }

        if (d->next != 0){ 
            decl_print(d->next);
        }
    }
}

void decl_resolve( struct decl *d ){
    if (d != NULL) {
        // resolve this decl
        // add to symbol table
        if (d->next != NULL) {
            decl_resolve(d->next);
        }
    }
}

struct type *decl_typecheck(struct type *a, struct type *b){
    if (a->kind != b->kind){
        fprintf(stderr,"typecheck error\n");
    }
    return a;
}
