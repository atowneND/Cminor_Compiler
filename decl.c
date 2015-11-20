#include "decl.h"
#include "type.h"
#include "expr.h"
#include "scope.h"
#include "symbol.h"
#include "param_list.h"
#include "stmt.h"
#include <stdlib.h>

extern int indent;
extern int scope_ctr;
extern int error_counter;

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
    if (d == NULL) {
        return;
    }

    // create the symbol structure
    symbol_t kind;
    if (scope_ctr <=1){
        kind = SYMBOL_GLOBAL;
    }else{
        kind = SYMBOL_LOCAL;
    }
    struct symbol *sym = symbol_create(kind, d->type, d->name);
    d->symbol = sym;
    // no redeclarations
    if (scope_lookup_local(d->name) != NULL) {
        fprintf(stderr,"No redeclarations allowed: %s\n",d->name);
        error_counter += 1;
    }

    // add to symbol table
    scope_bind(d->name,sym);

    // resolve components of decl
    expr_resolve(d->value);
    if (d->code != NULL) {
        scope_enter();
        param_list_resolve(d->type->params);
        stmt_resolve(d->code);
        scope_exit();
    }

    decl_resolve(d->next);
}

struct type *decl_typecheck(struct decl *d){
    if (d == NULL) {
        return type_create(TYPE_VOID,0,0,0);
    }
    // if d is global and right side is not constant, return error
    struct symbol *sym = scope_lookup(d->name);
    if (sym->kind == SYMBOL_GLOBAL){
        if (d->value != NULL){
        }
        if (d->code != NULL){
        }
    }

    // type to expression
    if (d->value != NULL){
        struct type *e = expr_typecheck(d->value);
        if ( d->type->kind != e->kind){
            error_counter += 1;
            printf("Error #%i ",error_counter);
            printf("type error: invalid declaration of ");
            type_print(d->type);
            printf(" (%s) = ",d->name);
            type_print(d->value->type);
            literal_print(d->value);
        }
        // expression list
        struct expr *tmp = d->value->next;
        while (tmp != NULL){
            e = expr_typecheck(tmp);
            if ( d->type->kind != e->kind){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: invalid declaration of ");
                type_print(d->type);
                printf(" (%s) = ",d->name);
                type_print(d->value->type);
                literal_print(d->value);
            }
            tmp = tmp->next;
        }
    }

    // return value
    stmt_typecheck(d->code, d->type);

    // function calls
    
    // next decl in the list
    decl_typecheck(d->next);
    return d->type;
}
