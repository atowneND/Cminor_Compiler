#include "expr.h"
#include "scope.h"
#include "param_list.h"
#include <stdlib.h>

extern int indent;
extern int error_counter;

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

    return new_expression;
}

void expr_append(struct expr *original_list, struct expr *new_expr){
    if (original_list->next != 0) {
        expr_append( original_list->next, new_expr);
    } else {
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

    return new_expression;
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

struct type *expr_typecheck(struct expr *e){
    if (e == NULL) {
        return type_create(TYPE_VOID,0,0,0);
    }
    struct type *l = malloc(sizeof(struct type));
    struct type *r = malloc(sizeof(struct type));
    switch (e->kind){
        case (EXPR_ADD):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot add ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_SUB):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                if (l->kind == TYPE_VOID) { // unary minor
                    e->type = type_create(TYPE_INTEGER,0,0,0);
                } else {
                    error_counter += 1;
                    printf("Error #%i ",error_counter);
                    printf("type error: cannot subtract ");
                    type_print(l);
                    literal_print(e->left);
                    printf(" from ");
                    type_print(r);
                    literal_print(e->right);
                    printf("\n");
                }
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_MUL):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot multiply ");
                type_print(l);
                literal_print(e->left);
                printf(" and ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_DIV):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot divide ");
                type_print(l);
                literal_print(e->left);
                printf(" by ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_INCREMENT):
            l = expr_typecheck(e->left);
            if (l->kind != TYPE_INTEGER){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot increment ");
                type_print(l);
                literal_print(e->left);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_DECREMENT):
            l = expr_typecheck(e->left);
            if (l->kind != TYPE_INTEGER){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot decrement ");
                type_print(l);
                literal_print(e->left);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_NOT):
            r = expr_typecheck(e->right);
            if (r->kind != TYPE_BOOLEAN){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot negate ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_POWER):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot raise ");
                type_print(l);
                literal_print(e->left);
                printf(" to power ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_MODULO):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot take modulus of ");
                type_print(l);
                literal_print(e->left);
                printf(" and ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_INTEGER,0,0,0);
            break;
        case (EXPR_LESS_THAN):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_GREATER_THAN):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_LESS_THAN_OR_EQUAL):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_GREATER_THAN_OR_EQUAL):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_INTEGER) || (r->kind != TYPE_INTEGER)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_EQUIVALENCE_COMPARISON):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind == TYPE_FUNCTION) || (r->kind == TYPE_FUNCTION)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare equivalence of functions\n");
            } else if ((l->kind == TYPE_ARRAY) || (r->kind == TYPE_ARRAY)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare equivalence of arrays\n");
            } else if (l->kind != r->kind){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare equivalence of ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_NONEQUIVALENCE_COMPARISON):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind == TYPE_FUNCTION) || (r->kind == TYPE_FUNCTION)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare equivalence of functions\n");
            } else if ((l->kind == TYPE_ARRAY) || (r->kind == TYPE_ARRAY)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare equivalence of arrays\n");
            } else if (l->kind != r->kind){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare equivalence of ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_AND):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_BOOLEAN) || (r->kind != TYPE_BOOLEAN)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_OR):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            if ((l->kind != TYPE_BOOLEAN) || (r->kind != TYPE_BOOLEAN)){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot compare ");
                type_print(l);
                literal_print(e->left);
                printf(" to ");
                type_print(r);
                literal_print(e->right);
                printf("\n");
            }
            e->type = type_create(TYPE_BOOLEAN,0,0,0);
            break;
        case (EXPR_ASSIGNMENT):
            l = expr_typecheck(e->left);
            r = expr_typecheck(e->right);
            //if ((l->kind == TYPE_FUNCTION) || (r->kind == TYPE_FUNCTION)){
            if (l->kind == TYPE_FUNCTION){
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot assign a function\n");
            } else if (l->kind != r->kind) {
                error_counter += 1;
                printf("Error #%i ",error_counter);
                printf("type error: cannot assign ");
                type_print(r);
                literal_print(e->right);
                printf(" to ");
                type_print(l);
                literal_print(e->left);
                printf("\n");
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
            e->type = expr_typecheck(e->left);
            break;
        case (EXPR_FUNCTION_CALL):
            param_list_typecheck();
            e->type = e->left->symbol->type->subtype;
            break;
        case (EXPR_ARRAY_INDEX):
            e->type = type_create(TYPE_ARRAY, 0, 0, 0);
            expr_typecheck(e->next_array_dimension);
            break;
    }
    return e->type;
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
            printf(" (%s[%i])",e->left->name,e->right->literal_value);
            break;
        case (TYPE_FUNCTION):
            printf(" (%s)",e->left->name);
            break;
        case (TYPE_VOID):
            break;
    }
}
