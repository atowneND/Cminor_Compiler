#include "param_list.h"
#include "scope.h"
#include "type.h"
#include <stdlib.h>
#include "decl.h"

extern int indent;

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
    struct symbol *sym = symbol_create(SYMBOL_PARAM, p->type, p->name);
    if (scope_lookup_local(p->name) != NULL) {
        fprintf(stderr,"No redeclarations allowed: %s\n",p->name);
        return;
    }

    scope_bind(p->name,sym);
    param_list_resolve(p->next);
}

void param_list_typeset(struct decl *d){
    if (d == NULL) return;
    struct symbol *sym = scope_lookup(d->name);
    printf("name: %s\n",d->name);
}

//void param_list_typecheck(struct param_list *p, struct type *subtype_list, struct decl *d){
//    printf("p->name=%s, type=%i; check_type=%i\n",p->name,p->type->kind,subtype_list->kind);
//    param_list_typecheck(p->next, d->next->type->subtype, d->next);
//}
