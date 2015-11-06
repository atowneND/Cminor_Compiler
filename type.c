#include "type.h"
#include "param_list.h"
#include <stdlib.h>

extern int indent;

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype, struct expr *expression){
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
        if (t->kind != 0) {
            switch (t->kind){
                case (TYPE_BOOLEAN):
                    printf("boolean");
                    break;
                case (TYPE_CHARACTER):
                    printf("character");
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
}
