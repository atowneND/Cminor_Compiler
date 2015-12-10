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

void type_print_error( struct type *t ) {
    if (t != NULL) {
        switch (t->kind){
            case (TYPE_BOOLEAN):
                fprintf(stderr,"boolean");
                break;
            case (TYPE_CHARACTER):
                fprintf(stderr,"char");
                break;
            case (TYPE_INTEGER):
                fprintf(stderr,"integer");
                break;
            case (TYPE_STRING):
                fprintf(stderr,"string");
                break;
            case (TYPE_ARRAY):
                fprintf(stderr,"array ");
                struct expr *tmp =  malloc(sizeof(struct expr));
                tmp = t->expr;
                while (tmp != NULL){
                    fprintf(stderr,"[");
                    expr_print_error(tmp);
                    fprintf(stderr,"]");
                    tmp = tmp->next_array_dimension;
                }
                fprintf(stderr," ");
                if (t->subtype != 0){ 
                    type_print_error(t->subtype);
                }
                break;
            case (TYPE_FUNCTION):
                fprintf(stderr,"function ");
                type_print_error(t->subtype);
                fprintf(stderr," (");
                if (t->params){ 
                    param_list_print_error(t->params);
                }
                fprintf(stderr,")");
                //indent += 1;
                break;
            case (TYPE_VOID):
                fprintf(stderr,"void");
                break;
        }
    }
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
                printf("array ");
                struct expr *tmp =  malloc(sizeof(struct expr));
                tmp = t->expr;
                while (tmp != NULL){
                    printf("[");
                    expr_print(tmp);
                    printf("]");
                    tmp = tmp->next_array_dimension;
                }
                printf(" ");
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

const char *type_codegen(FILE *fd,struct type *t){
    if (t == NULL) {
        fprintf(stderr,"This should never happen. Check decl typechecking\n");
        return "0";
    }
    switch (t->kind){
        case (TYPE_BOOLEAN):
            return "quad";
            break;
        case (TYPE_CHARACTER):
            return "quad";
            break;
        case (TYPE_INTEGER):
            return "quad";
            break;
        case (TYPE_STRING):
            return "string";
            break;
        case (TYPE_ARRAY):
            fprintf(stderr,"Arrays not supported: cannot create this variable\n");
            break;
        case (TYPE_FUNCTION):
            return "quad";
            break;
        case (TYPE_VOID):
            return "quad";
            break;
    }
    return "";
}
