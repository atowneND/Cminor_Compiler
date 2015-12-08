#include "decl.h"
#include "type.h"
#include "expr.h"
#include "scope.h"
#include "param_list.h"
#include "stmt.h"
#include <stdlib.h>

extern int indent;
extern int scope_ctr;
extern int error_counter;
extern struct hash_table_node *head_hash_table_node;

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
    new_declaration->symbol = 0;
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
        return;
    }

    // add to symbol table
    scope_bind(d->name,sym);

    // resolve components of decl
    expr_resolve(d->value);
    if (d->code != NULL) {
        scope_enter();
        if (sym->type->kind==TYPE_FUNCTION) {
            sym->function_hash_table = head_hash_table_node;
        }
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
    if (sym != NULL) {
        if (sym->kind == SYMBOL_GLOBAL){
            if (d->value != NULL){
            }
            if (d->code != NULL){
            }
        }
    }

    if (d->value != NULL){
        // type to expression
        struct type *e = expr_typecheck(d->value,d);
        // if array, use subtype
        type_kind_t d_kind = d->type->kind;
        if (d_kind == TYPE_ARRAY){
            d_kind = d->type->subtype->kind;
        }
        if ( d_kind != e->kind){
            error_counter += 1;
            fprintf(stderr,"Error #%i ",error_counter);
            fprintf(stderr,"type error: invalid declaration of ");
            type_print_error(d->type);
            fprintf(stderr," (%s) = ",d->name);
            type_print_error(d->value->type);
            literal_print_error(d->value);
        }
        // expression list
        struct expr *tmp = d->value->next;
        while (tmp != NULL){
            e = expr_typecheck(tmp,d);
            if ( d_kind != e->kind){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: invalid declaration of ");
                type_print_error(d->type);
                fprintf(stderr," (%s) = ",d->name);
                type_print_error(d->value->type);
                literal_print_error(d->value);
            }
            tmp = tmp->next;
        }
    }

    // return value (function definitions)
    stmt_typecheck(d->code, d->type, d);
    
    // next decl in the list
    decl_typecheck(d->next);
    return d->type;
}

void decl_codegen(struct decl *d){
    printf("codegen for decl\n");
}
