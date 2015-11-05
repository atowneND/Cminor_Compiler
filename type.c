#include "type.h"
#include "param_list.h"
#include <stdlib.h>

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype ){
    // create new struct
    struct type * new_type = malloc(sizeof(struct type *));
    new_type->kind = kind;
    new_type->params = params;
    new_type->subtype = subtype;

    // recurse to param_list
    // recurse to subtype

    return new_type;
}

void          type_print( struct type *t );
