#include "param_list.h"
#include <stdlib.h>

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next ){
    struct param_list * new_param_list = malloc(sizeof(struct param_list *));
    new_param_list->name = name;
    new_param_list->type = type;
    new_param_list->next = next;

    return new_param_list;
}

void param_list_print( struct param_list *a );
