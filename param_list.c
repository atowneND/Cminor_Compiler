#include "param_list.h"
#include <stdlib.h>

struct param_list * param_list_create(
        char *name,
        struct type *type,
        struct param_list *next 
    ){
    // create new struct
    struct param_list *new_param_list = malloc(sizeof(struct param_list));

    new_param_list->name = name;
    new_param_list->type = type;
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
/*    printf("%s: ",a->name);
    type_print(a->type);
    if (a->next != 0){
        printf(", "); 
        param_list_print(a->next);
    }*/
}
