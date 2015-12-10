#include "param_list.h"
#include "scope.h"
#include "type.h"
#include <stdlib.h>
#include "decl.h"

extern int indent;
extern int error_counter;
extern struct hash_table_node *head_hash_table_node;
extern int param_ctr;

struct param_list * param_list_create(
        char *name,
        struct type *type,
        struct param_list *next 
    ){
    // create new struct
    struct param_list *new_param_list = malloc(sizeof(struct param_list));

    new_param_list->name = name;
    new_param_list->type = type;
    new_param_list->symbol = 0;
    new_param_list->next = next;

    return new_param_list;
}

void param_list_append( struct param_list *original_params, struct param_list *new_param){
    if (original_params->next != 0) {
        param_list_append( original_params->next, new_param );
    } else {
        original_params->next = new_param;
        new_param->next = 0;
        return;
    }
}

void param_list_print_error( struct param_list *a ){
    if (a != NULL){
        printf("%s: ",a->name);
        type_print_error(a->type);
        if (a->next != 0){
            fprintf(stderr,", "); 
            param_list_print_error(a->next);
        }
    }
}

void param_list_print( struct param_list *a ){
    if (a != NULL){
        printf("%s: ",a->name);
        type_print(a->type);
        if (a->next != 0){
            printf(", "); 
            param_list_print(a->next);
        }
    }
}

void param_list_resolve(struct param_list *p){
    if (p == NULL) {
        return;
    }
    struct symbol *sym = symbol_create(SYMBOL_PARAM, p->type, p->name, 0 );
    if (scope_lookup_local(p->name) != NULL) {
        fprintf(stderr,"No redeclarations allowed: %s\n",p->name);
        return;
    }

    scope_bind(p->name,sym);
    param_list_resolve(p->next);
    param_ctr += 1;
}

void param_list_typecheck(const char *fname,struct expr *e_params,struct decl *d){
//    printf("function name = %s    ",fname);
    struct symbol *sym = scope_lookup(fname);
    if (!sym) return;
    struct hash_table_node *function_ht = sym->function_hash_table;
//    printf("etype: %i\n",e_params->type->kind);
    type_kind_t expected_type;
    type_kind_t given_type;
    struct param_list *p;
    p = sym->type->params;

    while ((p != NULL) && (e_params != NULL)) { 
        expr_typecheck(e_params,d);
        expected_type = p->type->kind;
        given_type = e_params->type->kind;
        if (expected_type != given_type){
            error_counter += 1;
            sym = scope_lookup_function(p->name,function_ht);
            printf("Typechecking error: Function %s parameter %i is expected to be type ",fname,sym->which);
            type_print(sym->type);
            printf(" but argument given was type ");
            type_print(e_params->type);
            printf("\n");
        }
        p = p->next;
        e_params = e_params->next;
    }

    if (p==NULL) {
        if (e_params != NULL) {
            error_counter += 1;
            printf("Typechecking error: Function %s is expecting fewer paramaters\n",fname);
        }
    } else if (e_params == NULL) {
        if (p != NULL) {
            error_counter += 1;
            printf("Typechecking error: Function %s is expecting more parameters\n",fname);
        }
    }
    //sym->type->params->next->type->kind
}

void param_codegen_push(struct param_list *p, FILE *fd){
    if (!p){
        return;
    }
    my_registers_t param_reg = register_alloc(ARGUMENT);
    fprintf(fd,"    pushq %s # save argument on the stack\n",register_name(param_reg));
    param_codegen_push(p->next, fd);
}

void param_codegen_call(struct expr *e, struct symbol *s, FILE *fd){
    if (!e){
        return;
    }
    // allocate an argument register
    my_registers_t param_reg = register_alloc(ARGUMENT);

    // recurse to allocate all registers
    param_codegen_call(e->next,s,fd);

    // move parameter values to param registers
    expr_codegen(e,fd);
    fprintf(fd,"    mov %s, %s\n",register_name(e->reg),register_name(param_reg));
    register_free(e->reg);
    e->reg = param_reg;
}
