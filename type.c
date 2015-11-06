#include "type.h"
#include "param_list.h"
#include <stdlib.h>

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype, struct expr *expression){
    // create new struct
    struct type *ptr_new_type = malloc(sizeof(struct type *));
    struct type new_type;
    ptr_new_type = &new_type;

    new_type.kind = kind;
    new_type.params = params;
    new_type.subtype = subtype;
    new_type.expr = expression;

    return ptr_new_type;
}

void type_print( struct type *t ) {
/*    switch (t->kind){
        case (TYPE_BOOLEAN):
            printf("boolean");
        case (TYPE_CHARACTER):
            printf("character");
        case (TYPE_INTEGER):
            printf("integer");
        case (TYPE_STRING):
            printf("string");
        case (TYPE_ARRAY):
            printf("array [");
            expr_print(t->expr);
            printf("]");
            type_print(t->subtype);
        case (TYPE_FUNCTION):
            printf("function(");
            param_list_print(t->params);
            printf(")");
        case (TYPE_VOID):
            printf("void");
    }*/
}
