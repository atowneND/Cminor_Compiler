#include "expr.h"
#include <stdlib.h>

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ){
    struct expr * new_expression = malloc(sizeof(struct expr *));
    new_expression->kind = kind;
    new_expression->left = left;
    new_expression->right = right;

    return new_expression;
}

struct expr * expr_create_name( const char *n ){
    struct expr * new_expression = malloc(sizeof(struct expr *));
    new_expression->kind = EXPR_IDENTIFIER;
    new_expression->name = n;
    
    return new_expression;
}

struct expr * expr_create_boolean_literal( int c ){
    struct expr * new_expression = malloc(sizeof(struct expr *));
    new_expression->kind = EXPR_BOOLEAN_LITERAL;
    new_expression->literal_value = c;

    return new_expression;
}

struct expr * expr_create_integer_literal( int c ){
    struct expr * new_expression = malloc(sizeof(struct expr *));
    new_expression->kind = EXPR_INTEGER_LITERAL;
    new_expression->literal_value = c;

    return new_expression;
}

struct expr * expr_create_character_literal( int c ){
    struct expr * new_expression = malloc(sizeof(struct expr *));
    new_expression->kind = EXPR_CHARACTER_LITERAL;
    new_expression->literal_value = c;

    return new_expression;
}

struct expr * expr_create_string_literal( const char *str ){
    struct expr * new_expression = malloc(sizeof(struct expr *));
    new_expression->kind = EXPR_STRING_LITERAL;
    new_expression->string_literal = str;

    return new_expression;
}

void expr_print( struct expr *e ){
}

