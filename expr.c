#include "decl.h"
#include "expr.h"
#include "scope.h"
#include "param_list.h"
#include <stdlib.h>
#include <string.h>

extern int indent;
extern int error_counter;
extern int string_counter;
int condition_counter = 0;
int done_counter = 0;

struct expr * expr_create(
        expr_t kind,
        struct expr *left,
        struct expr *right,
        struct expr *next
    ){
    // create new struct
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = kind;
    new_expression->left = left;
    new_expression->right = right;
    new_expression->next = next;
    new_expression->next_array_dimension = 0;

    new_expression->name = 0;
    new_expression->symbol = 0;
    new_expression->literal_value = 0;
    new_expression->string_literal = 0;

    new_expression->type = 0;
    new_expression->reg = 0;

    return new_expression;
}

void expr_append(struct expr *original_list, struct expr *new_expr){
    if (original_list->next != 0) {
        // search for end of list
        expr_append( original_list->next, new_expr);
    } else {
        // add to end of list
        original_list->next = new_expr;
        new_expr->next = 0;
        return;
    }
}

struct expr * expr_create_name( const char *n ){
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = EXPR_IDENTIFIER;
    new_expression->left = 0;
    new_expression->right = 0;
    new_expression->next = 0;
    new_expression->next_array_dimension = 0;

    new_expression->name = n;
    new_expression->symbol = 0;
    new_expression->literal_value = 0;
    new_expression->string_literal = 0;

    new_expression->type = 0;
    new_expression->reg = 0;
    
    return new_expression;
}

struct expr * expr_create_boolean_literal( int c ){
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = EXPR_BOOLEAN_LITERAL;
    new_expression->left = 0;
    new_expression->right = 0;
    new_expression->next = 0;
    new_expression->next_array_dimension = 0;

    new_expression->name = 0;
    new_expression->symbol = 0;
    new_expression->literal_value = c;
    new_expression->string_literal = 0;

    new_expression->type = 0;
    new_expression->reg = 0;

    return new_expression;
}

struct expr * expr_create_integer_literal( int c ){
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = EXPR_INTEGER_LITERAL;
    new_expression->left = 0;
    new_expression->right = 0;
    new_expression->next = 0;
    new_expression->next_array_dimension = 0;

    new_expression->name = 0;
    new_expression->symbol = 0;
    new_expression->literal_value = c;
    new_expression->string_literal = 0;

    new_expression->type = 0;
    new_expression->reg = 0;

    return new_expression;
}

struct expr * expr_create_character_literal( int c ){
    struct expr *new_expression = malloc(sizeof(struct expr));
    
    new_expression->kind = EXPR_CHARACTER_LITERAL;
    new_expression->left = 0;
    new_expression->right = 0;
    new_expression->next = 0;
    new_expression->next_array_dimension = 0;

    new_expression->name = 0;
    new_expression->symbol = 0;
    new_expression->literal_value = c;
    new_expression->string_literal = 0;

    new_expression->type = 0;
    new_expression->reg = 0;

    return new_expression;
}

struct expr * expr_create_string_literal( const char *str ){
    struct expr *new_expression = malloc(sizeof(struct expr));
    
    new_expression->kind = EXPR_STRING_LITERAL;
    new_expression->left = 0;
    new_expression->right = 0;
    new_expression->next = 0;
    new_expression->next_array_dimension = 0;

    new_expression->name = 0;
    new_expression->symbol = 0;
    new_expression->literal_value = 0;
    new_expression->string_literal = str;

    new_expression->type = 0;
    new_expression->reg = 0;

    return new_expression;
}

void expr_print_error( struct expr *e ){
    if (e != NULL) {
        switch (e->kind){
            case (EXPR_ADD):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"+");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_SUB):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"-");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_MUL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"*");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_DIV):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"/");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_INCREMENT):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"++");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_DECREMENT):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"--");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_NOT):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"!");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_POWER):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"^");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_MODULO):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"%%");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_LESS_THAN):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," < ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_GREATER_THAN):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," > ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_LESS_THAN_OR_EQUAL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," <= ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_GREATER_THAN_OR_EQUAL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," >= ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_EQUIVALENCE_COMPARISON):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," == ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_NONEQUIVALENCE_COMPARISON):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," != ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_AND):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," && ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_OR):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," || ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_ASSIGNMENT):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr," = ");
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_BOOLEAN_LITERAL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"%i",e->literal_value);
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_INTEGER_LITERAL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"%i",e->literal_value);
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_CHARACTER_LITERAL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"'%c'",e->literal_value);
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_STRING_LITERAL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"%s",e->string_literal);
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_IDENTIFIER):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"%s",e->name);
                if (e->right != 0) expr_print_error(e->right);
                break;
            case (EXPR_PARENTHESES):
                fprintf(stderr,"(");
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,")");
                break;
            case (EXPR_FUNCTION_CALL):
                if (e->left != 0) expr_print_error(e->left);
                fprintf(stderr,"(");
                if (e->right != 0) expr_print_error(e->right);
                fprintf(stderr,")");
                break;
            case (EXPR_ARRAY_INDEX):
                if (e->left != 0) expr_print_error(e->left);
                struct expr *tmp = malloc(sizeof(struct expr));
                tmp = e->right;
                while (tmp != NULL){
                    fprintf(stderr,"[");
                    expr_print_error(tmp);
                    fprintf(stderr,"]");
                    tmp = tmp->next_array_dimension;
                }
                break;
        }
        if (e->next != NULL){
            fprintf(stderr,", "); 
            expr_print_error(e->next);
        }
    }
}

void expr_print( struct expr *e ){
    if (e != NULL) {
        switch (e->kind){
            case (EXPR_ADD):
                if (e->left != 0) expr_print(e->left);
                printf("+");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_SUB):
                if (e->left != 0) expr_print(e->left);
                printf("-");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_MUL):
                if (e->left != 0) expr_print(e->left);
                printf("*");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_DIV):
                if (e->left != 0) expr_print(e->left);
                printf("/");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_INCREMENT):
                if (e->left != 0) expr_print(e->left);
                printf("++");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_DECREMENT):
                if (e->left != 0) expr_print(e->left);
                printf("--");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_NOT):
                if (e->left != 0) expr_print(e->left);
                printf("!");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_POWER):
                if (e->left != 0) expr_print(e->left);
                printf("^");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_MODULO):
                if (e->left != 0) expr_print(e->left);
                printf("%%");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_LESS_THAN):
                if (e->left != 0) expr_print(e->left);
                printf(" < ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_GREATER_THAN):
                if (e->left != 0) expr_print(e->left);
                printf(" > ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_LESS_THAN_OR_EQUAL):
                if (e->left != 0) expr_print(e->left);
                printf(" <= ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_GREATER_THAN_OR_EQUAL):
                if (e->left != 0) expr_print(e->left);
                printf(" >= ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_EQUIVALENCE_COMPARISON):
                if (e->left != 0) expr_print(e->left);
                printf(" == ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_NONEQUIVALENCE_COMPARISON):
                if (e->left != 0) expr_print(e->left);
                printf(" != ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_AND):
                if (e->left != 0) expr_print(e->left);
                printf(" && ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_OR):
                if (e->left != 0) expr_print(e->left);
                printf(" || ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_ASSIGNMENT):
                if (e->left != 0) expr_print(e->left);
                printf(" = ");
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_BOOLEAN_LITERAL):
                if (e->left != 0) expr_print(e->left);
                printf("%i",e->literal_value);
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_INTEGER_LITERAL):
                if (e->left != 0) expr_print(e->left);
                printf("%i",e->literal_value);
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_CHARACTER_LITERAL):
                if (e->left != 0) expr_print(e->left);
                printf("'%c'",e->literal_value);
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_STRING_LITERAL):
                if (e->left != 0) expr_print(e->left);
                printf("%s",e->string_literal);
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_IDENTIFIER):
                if (e->left != 0) expr_print(e->left);
                printf("%s",e->name);
                if (e->right != 0) expr_print(e->right);
                break;
            case (EXPR_PARENTHESES):
                printf("(");
                if (e->left != 0) expr_print(e->left);
                printf(")");
                break;
            case (EXPR_FUNCTION_CALL):
                if (e->left != 0) expr_print(e->left);
                printf("(");
                if (e->right != 0) expr_print(e->right);
                printf(")");
                break;
            case (EXPR_ARRAY_INDEX):
                if (e->left != 0) expr_print(e->left);
                struct expr *tmp = malloc(sizeof(struct expr));
                tmp = e->right;
                while (tmp != NULL){
                    printf("[");
                    expr_print(tmp);
                    printf("]");
                    tmp = tmp->next_array_dimension;
                }
                break;
        }
        if (e->next != NULL){
            printf(", "); 
            expr_print(e->next);
        }
    }

}

void expr_resolve(struct expr *e){
    if (e == NULL) {
        return;
    }

    expr_resolve(e->left);
    expr_resolve(e->right);

    if (e->kind==EXPR_IDENTIFIER){
        struct symbol *s = scope_lookup(e->name);
        if (s != NULL){
            e->symbol = s;
            char *this_variable = malloc(sizeof(char) * 10);
            switch (s->kind){
                case SYMBOL_LOCAL:
                    sprintf(this_variable,"LOCAL %i",s->which);
                    break;
                case SYMBOL_GLOBAL:
                    sprintf(this_variable,"GLOBAL %s",s->name);
                    break;
                case SYMBOL_PARAM:
                    sprintf(this_variable,"PARAM %i",s->which);
                    break;
                default:
                    fprintf(stderr,"Scope not recognized for symbol: %s\n",e->name);
                    error_counter += 1;
                    break;
            }
            printf("%s resolved to %s\n",e->name,this_variable);
        } else {
            fprintf(stderr,"Symbol %s not declared\n",e->name);
            error_counter += 1;
        }
    }
    expr_resolve(e->next);
}

struct type *expr_typecheck(struct expr *e, struct decl *d){
    if (e == NULL) {
        return type_create(TYPE_VOID,0,0,0);
    }
    struct type *l = malloc(sizeof(struct type));
    struct type *r = malloc(sizeof(struct type));
    switch (e->kind){
        case (EXPR_ADD):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot add ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_SUB):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                if (l->kind == TYPE_VOID) { // unary minor
                    e->type = type_create(TYPE_INTEGER,0,0,0);
                } else {
                    error_counter += 1;
                    fprintf(stderr,"Error #%i ",error_counter);
                    fprintf(stderr,"type error: cannot subtract ");
                    type_print_error(l);
                    literal_print_error(e->left);
                    fprintf(stderr," from ");
                    type_print_error(r);
                    literal_print_error(e->right);
                    fprintf(stderr,"\n");
                }
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_MUL):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot multiply ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," and ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_DIV):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot divide ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," by ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_INCREMENT):
            l = expr_typecheck(e->left,d);
            if (l->kind != TYPE_INTEGER){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot increment ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_DECREMENT):
            l = expr_typecheck(e->left,d);
            if (l->kind != TYPE_INTEGER){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot decrement ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_NOT):
            r = expr_typecheck(e->right,d);
            if (r->kind != TYPE_BOOLEAN){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot negate ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_POWER):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot raise ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to power ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_MODULO):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot take modulus of ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," and ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_LESS_THAN):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_GREATER_THAN):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_LESS_THAN_OR_EQUAL):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_GREATER_THAN_OR_EQUAL):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_EQUIVALENCE_COMPARISON):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind == TYPE_FUNCTION) || (r->kind == TYPE_FUNCTION)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare equivalence of functions\n");
            } else if ((l->kind == TYPE_ARRAY) || (r->kind == TYPE_ARRAY)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare equivalence of arrays\n");
            } else if (l->kind != r->kind){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare equivalence of ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_NONEQUIVALENCE_COMPARISON):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind == TYPE_FUNCTION) || (r->kind == TYPE_FUNCTION)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare equivalence of functions\n");
            } else if ((l->kind == TYPE_ARRAY) || (r->kind == TYPE_ARRAY)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare equivalence of arrays\n");
            } else if (l->kind != r->kind){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare equivalence of ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_AND):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_BOOLEAN) || (r->kind != TYPE_BOOLEAN)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_OR):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            if ((l->kind != TYPE_BOOLEAN) || (r->kind != TYPE_BOOLEAN)){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: cannot compare ");
                type_print_error(l);
                literal_print_error(e->left);
                fprintf(stderr," to ");
                type_print_error(r);
                literal_print_error(e->right);
                fprintf(stderr,"\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_ASSIGNMENT):
            /**************************/
            l = expr_typecheck(e->left,d);
            if (l->kind == TYPE_ARRAY) {
                type_kind_t expected_type;
                if (l->subtype != NULL) { 
                    expected_type = l->subtype->kind;
                } else {
                    expected_type = l->kind;
                }
                struct expr *elist = e->right;
                while (elist != NULL) {
                    r = expr_typecheck(elist,d);
                    type_kind_t given_type = elist->type->kind;
                    if (expected_type != given_type) {
                        error_counter += 1;
                        fprintf(stderr,"Error #%i ",error_counter);
                        fprintf(stderr,"type error: cannot assign ");
                        type_print_error(r);
                        literal_print_error(elist);
                        fprintf(stderr," to an element of ");
                        type_print_error(l);
                        struct expr *etmp = e->left;
                        if (e->left->kind == EXPR_ARRAY_INDEX){
                            etmp = etmp->left;
                        }
                        struct type *ttmp = etmp->type->subtype;
                        while (ttmp->kind == TYPE_ARRAY) {
                            ttmp = ttmp->subtype;
                        }
                        literal_print_error(etmp);
                        fprintf(stderr,"\n");
                    }
                    elist = elist->next;
                }
            /**************************/
            } else { 
                r = expr_typecheck(e->right,d);
                //if ((l->kind == TYPE_FUNCTION) || (r->kind == TYPE_FUNCTION)){
                if (l->kind == TYPE_FUNCTION){
                    error_counter += 1;
                    fprintf(stderr,"Error #%i ",error_counter);
                    fprintf(stderr,"type error: cannot assign a function\n");
                } else if (l->kind != r->kind) {
                    error_counter += 1;
                    fprintf(stderr,"Error #%i ",error_counter);
                    fprintf(stderr,"type error: cannot assign ");
                    type_print_error(r);
                    literal_print_error(e->right);
                    fprintf(stderr," to ");
                    type_print_error(l);
                    literal_print_error(e->left);
                    fprintf(stderr,"\n");
                }
            }
            e->type = type_create(l->kind,0,0,0);
            break;
        case (EXPR_BOOLEAN_LITERAL):
            e->type = type_create(TYPE_BOOLEAN, 0, 0, 0);
            break;
        case (EXPR_INTEGER_LITERAL):
            e->type = type_create(TYPE_INTEGER, 0, 0, 0);
            break;
        case (EXPR_CHARACTER_LITERAL):
            e->type = type_create(TYPE_CHARACTER, 0, 0, 0);
            break;
        case (EXPR_STRING_LITERAL):
            e->type = type_create(TYPE_STRING, 0, 0, 0);
            break;
        case (EXPR_IDENTIFIER):
            e->type = e->symbol->type;
            break;
        case (EXPR_PARENTHESES):
            e->type = expr_typecheck(e->left,d);
            break;
        case (EXPR_FUNCTION_CALL):
            // check parameters
            param_list_typecheck(e->left->name,e->right,d);
            e->type = e->left->symbol->type->subtype;
            break;
        case (EXPR_ARRAY_INDEX):
            l = expr_typecheck(e->left,d);
            r = expr_typecheck(e->right,d);
            e->type = type_create(TYPE_ARRAY, 0, 0, 0);
            expr_typecheck(e->next_array_dimension,d);
            break;
    }
    return e->type;
}

void literal_print_error(struct expr *e){
    if (e->type == NULL) return;
    switch (e->type->kind){
        case (TYPE_BOOLEAN):
            fprintf(stderr," (%i)",e->literal_value);
            break;
        case (TYPE_CHARACTER):
            fprintf(stderr," (%c)",e->literal_value);
            break;
        case (TYPE_INTEGER):
            fprintf(stderr," (%i)",e->literal_value);
            break;
        case (TYPE_STRING):
            fprintf(stderr," (%s)",e->string_literal);
            break;
        case (TYPE_ARRAY):
            fprintf(stderr," (%s)",e->name);
            break;
        case (TYPE_FUNCTION):
            fprintf(stderr," (%s)",e->left->name);
            break;
        case (TYPE_VOID):
            break;
    }
}

void literal_print(struct expr *e){
    if (e->type == NULL) return;
    switch (e->type->kind){
        case (TYPE_BOOLEAN):
            printf(" (%i)",e->literal_value);
            break;
        case (TYPE_CHARACTER):
            printf(" (%c)",e->literal_value);
            break;
        case (TYPE_INTEGER):
            printf(" (%i)",e->literal_value);
            break;
        case (TYPE_STRING):
            printf(" (%s)",e->string_literal);
            break;
        case (TYPE_ARRAY):
            printf(" (%s)",e->name);
            break;
        case (TYPE_FUNCTION):
            printf(" (%s)",e->left->name);
            break;
        case (TYPE_VOID):
            break;
    }
}

void expr_codegen(struct expr *e, FILE *fd){
    if (!e) return;
    // TODO finish the other cases
    switch (e->kind){
        case EXPR_ADD:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    add %s, %s\n",register_name(e->left->reg),register_name(e->right->reg));

            // update AST
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_SUB:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    sub %s, %s\n",register_name(e->right->reg),register_name(e->left->reg));

            // update ast
            e->reg = e->left->reg;

            // cleanup
            register_free(e->right->reg);
            e->right->reg = -1;
            break;
        case EXPR_MUL:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    mov %s, %%rax\n",register_name(e->left->reg));
            fprintf(fd,"    imul %s\n",register_name(e->right->reg)); // implicitly multiply by %rax, leaves result in %rax
            fprintf(fd,"    mov %%rax, %s\n",register_name(e->right->reg)); // store result in right register
            
            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_DIV:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    movq %s, %%rax\n",register_name(e->left->reg));
            fprintf(fd,"    cltd\n"); // could have to be cdq0
            fprintf(fd,"    divq %s\n",register_name(e->right->reg)); // implicitly multiply by %rax, leaves result in %rax
            fprintf(fd,"    mov %%rax, %s\n",register_name(e->right->reg)); // store result in right register

            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_INCREMENT:
            // recurse
            expr_codegen(e->left,fd);

            // print to assembly file
            fprintf(fd,"    add $1, %s\n",register_name(e->left->reg));

            // update ast
            e->reg = e->left->reg;
            break;
        case EXPR_DECREMENT:
            // recurse
            expr_codegen(e->left,fd);

            // print to assembly file
            fprintf(fd,"    sub $1, %s\n",register_name(e->left->reg));

            // update ast
            e->reg = e->left->reg;
            break;
        case EXPR_NOT:
            // recurse
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    not %s\n",register_name(e->right->reg));
            fprintf(fd,"    and $0x1, %s\n",register_name(e->right->reg));

            // update ast
            e->reg = e->right->reg;
            break;
        case EXPR_POWER:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file

            // update ast

            // cleanup
            break;
        case EXPR_MODULO:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    movq %s, %%rax\n",register_name(e->left->reg));
            fprintf(fd,"    cltd\n"); // could have to be cdq0
            fprintf(fd,"    divq %s\n",register_name(e->right->reg)); // implicitly multiply by %rax, leaves result in %rax
            fprintf(fd,"    mov %%rdx, %s\n",register_name(e->right->reg)); // store result in right register

            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_LESS_THAN:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    cmpq %s, %s\n",register_name(e->right->reg),register_name(e->left->reg));
            fprintf(fd,"    jl cond%i\n",condition_counter);
            fprintf(fd,"# greater than or equal\n");
            fprintf(fd,"    mov $0, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            //fprintf(fd,"done:\n");
            fprintf(fd,"# less than\n");
            fprintf(fd,"cond%i:\n",condition_counter);
            fprintf(fd,"    mov $1, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            fprintf(fd,"done%i:\n",done_counter);
            condition_counter += 1;
            done_counter += 1;

            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_GREATER_THAN:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    cmpq %s, %s\n",register_name(e->right->reg),register_name(e->left->reg));
            fprintf(fd,"    jg cond%i\n",condition_counter);
            fprintf(fd,"# less than or equal\n");
            fprintf(fd,"    mov $0, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            //fprintf(fd,"done:\n");
            fprintf(fd,"# greater than\n");
            fprintf(fd,"cond%i:\n",condition_counter);
            fprintf(fd,"    mov $1, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            fprintf(fd,"done%i:\n",done_counter);
            condition_counter += 1;
            done_counter += 1;

            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_LESS_THAN_OR_EQUAL:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    cmpq %s, %s\n",register_name(e->right->reg),register_name(e->left->reg));
            fprintf(fd,"    jle cond%i\n",condition_counter);
            fprintf(fd,"# greater than\n");
            fprintf(fd,"    mov $0, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            //fprintf(fd,"done:\n");
            fprintf(fd,"# less than or equal\n");
            fprintf(fd,"cond%i:\n",condition_counter);
            fprintf(fd,"    mov $1, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            fprintf(fd,"done%i:\n",done_counter);
            condition_counter += 1;
            done_counter += 1;

            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_GREATER_THAN_OR_EQUAL:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    cmpq %s, %s\n",register_name(e->right->reg),register_name(e->left->reg));
            fprintf(fd,"    jge cond%i\n",condition_counter);
            fprintf(fd,"# less than\n");
            fprintf(fd,"    mov $0, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            //fprintf(fd,"done:\n");
            fprintf(fd,"# greater than or equal\n");
            fprintf(fd,"cond%i:\n",condition_counter);
            fprintf(fd,"    mov $1, %s\n",register_name(e->right->reg));
            //fprintf(fd,"    jmp done\n");
            fprintf(fd,"    jmp done%i\n",done_counter);
            fprintf(fd,"done%i:\n",done_counter);
            condition_counter += 1;
            done_counter += 1;

            // update ast
            e->reg = e->right->reg;

            // cleanup
            register_free(e->left->reg);
            e->left->reg = -1;
            break;
        case EXPR_EQUIVALENCE_COMPARISON:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file

            // update ast

            // cleanup
            break;
        case EXPR_NONEQUIVALENCE_COMPARISON:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file

            // update ast

            // cleanup
            break;
        case EXPR_AND:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file

            // update ast

            // cleanup
            break;
        case EXPR_OR:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file

            // update ast

            // cleanup
            break;
        case EXPR_ASSIGNMENT:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // print to assembly file
            fprintf(fd,"    mov %s, %s\n",register_name(e->right->reg),register_name(e->left->reg));

            // update ast
            e->reg = e->left->reg;

            // cleanup
            register_free(e->right->reg);
            e->right->reg = -1;
            break;
        case EXPR_BOOLEAN_LITERAL:
            e->reg = register_alloc(SCRATCH);
            fprintf(fd,"    mov $%i, %s\n",e->literal_value, register_name(e->reg));
            break;
        case EXPR_INTEGER_LITERAL:
            e->reg = register_alloc(SCRATCH);
            fprintf(fd,"    mov $%d, %s\n",e->literal_value, register_name(e->reg));
            break;
        case EXPR_CHARACTER_LITERAL:
            e->reg = register_alloc(SCRATCH);
            fprintf(fd,"    mov $%d, %s\n",e->literal_value, register_name(e->reg));
            break;
        case EXPR_STRING_LITERAL:
            e->reg = register_alloc(SCRATCH);

            // print to assembly file
            fprintf(fd,".data\n    STR%i:\n",string_counter);
            fprintf(fd,"    .string %s\n",e->string_literal);
            fprintf(fd,".text\n");
            fprintf(fd,"    lea STR%i, %s\n",string_counter,register_name(e->reg));

            // cleanup
            string_counter += 1;
            break;
        case EXPR_IDENTIFIER:
            e->reg = register_alloc(SCRATCH);
            fprintf(fd,"    mov %s, %s\n",symbol_code(e->symbol,fd), register_name(e->reg));
            if (e->symbol->value != NULL) {
                e->symbol->value->reg = e->reg;
            }
            break;
        case EXPR_PARENTHESES:
            // recurse
            expr_codegen(e->left,fd);
            expr_codegen(e->right,fd);

            // no code for assembly file necessary
            // update ast
            e->reg = e->left->reg;
            break;
        case EXPR_FUNCTION_CALL:
            // evaluated after expr_ident

            // print to assembly file
            param_codegen_call(e->right, e->left->symbol, fd);
            fprintf(fd,"    call %s\n",e->left->name);

            // cleanup
            register_free_type(ARGUMENT);

            // update ast
            e->reg = e->left->reg;
            break;
        case EXPR_ARRAY_INDEX:
            break;
    }
}
