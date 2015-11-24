#include "type.h"
#include "param_list.h"
#include <stdlib.h>

extern int indent;

struct type * type_create( 
        type_kind_t kind,
        struct param_list *params,
        struct type *subtype,
        struct expr *expression
    ){
    // create new struct
    struct type *new_type = malloc(sizeof(struct type));

    new_type->kind = kind;
    new_type->params = params;
    new_type->subtype = subtype;
    new_type->expr = expression;

    return new_type;
}

void type_print( struct type *t ) {
    if (t != NULL) {
        switch (t->kind){
            case (TYPE_BOOLEAN):
                printf("boolean");
                break;
            case (TYPE_CHARACTER):
                printf("char");
                break;
            case (TYPE_INTEGER):
                printf("integer");
                break;
            case (TYPE_STRING):
                printf("string");
                break;
            case (TYPE_ARRAY):
                printf("array [");
                if (t->expr != 0){
                    expr_print(t->expr);
                }
                printf("] ");
                if (t->subtype != 0){ 
                    type_print(t->subtype);
                }
                break;
            case (TYPE_FUNCTION):
                printf("function ");
                type_print(t->subtype);
                printf(" (");
                if (t->params){ 
                    param_list_print(t->params);
                }
                printf(")");
                //indent += 1;
                break;
            case (TYPE_VOID):
                printf("void");
                break;
        }
    }
}

struct type *type_copy(struct type *t){
    struct type *new_type = malloc(sizeof(struct type));

    new_type->kind = t->kind;
    new_type->params = t->params;
    new_type->subtype = t->subtype;
    new_type->expr = t->expr;

    return new_type;
}

int type_compare(struct type *a, struct type *b){
    if (a->kind == b->kind){
        return 1;
    }else{
        return 0;
    }
}

void type_delete(struct type *t){
    free(t);
}
