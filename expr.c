#include "expr.h"
#include <stdlib.h>

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
    struct expr new_expression;
    ptr_new_expression = &new_expression;
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression.kind = EXPR_IDENTIFIER;
    new_expression.name = n;
    
    return ptr_new_expression;
}

struct expr * expr_create_boolean_literal( int c ){
    struct expr new_expression;
    ptr_new_expression = &new_expression;

    new_expression.kind = EXPR_BOOLEAN_LITERAL;
    new_expression.literal_value = c;

    return ptr_new_expression;
}

struct expr * expr_create_integer_literal( int c ){
    struct expr new_expression;
    ptr_new_expression = &new_expression;
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression.kind = EXPR_INTEGER_LITERAL;
    new_expression.literal_value = c;

    return ptr_new_expression;
}

struct expr * expr_create_character_literal( int c ){
    struct expr new_expression;
    ptr_new_expression = &new_expression;
    struct expr *new_expression = malloc(sizeof(struct expr));
    
    new_expression.kind = EXPR_CHARACTER_LITERAL;
    new_expression.literal_value = c;

    return ptr_new_expression;
}

struct expr * expr_create_string_literal( const char *str ){
    struct expr new_expression;
    ptr_new_expression = &new_expression;
    struct expr *new_expression = malloc(sizeof(struct expr));
    
    new_expression.kind = EXPR_STRING_LITERAL;
    new_expression.string_literal = str;

    return ptr_new_expression;
}

void expr_print( struct expr *e ){
/*    switch (e->kind){
        case (EXPR_ADD):
            expr_print(e->left);
            printf(" + ");
            expr_print(e->right);
        case (EXPR_SUB):
            expr_print(e->left);
            printf(" - ");
            expr_print(e->right);
        case (EXPR_MUL):
            expr_print(e->left);
            printf(" * ");
            expr_print(e->right);
        case (EXPR_DIV):
            expr_print(e->left);
            printf(" / ");
            expr_print(e->right);
        case (EXPR_INCREMENT):
            expr_print(e->left);
            printf(" ++ ");
            expr_print(e->right);
        case (EXPR_DECREMENT):
            expr_print(e->left);
            printf(" -- ");
            expr_print(e->right);
        case (EXPR_NOT):
            expr_print(e->left);
            printf(" ! ");
            expr_print(e->right);
        case (EXPR_POWER):
            expr_print(e->left);
            printf(" ^ ");
            expr_print(e->right);
        case (EXPR_MODULO):
            expr_print(e->left);
            printf(" %% ");
            expr_print(e->right);
        case (EXPR_LESS_THAN):
            expr_print(e->left);
            printf(" < ");
            expr_print(e->right);
        case (EXPR_GREATER_THAN):
            expr_print(e->left);
            printf(" > ");
            expr_print(e->right);
        case (EXPR_LESS_THAN_OR_EQUAL):
            expr_print(e->left);
            printf(" <= ");
            expr_print(e->right);
        case (EXPR_GREATER_THAN_OR_EQUAL):
            expr_print(e->left);
            printf(" >= ");
            expr_print(e->right);
        case (EXPR_EQUIVALENCE_COMPARISON):
            expr_print(e->left);
            printf(" == ");
            expr_print(e->right);
        case (EXPR_NONEQUIVALENCE_COMPARISON):
            expr_print(e->left);
            printf(" != ");
            expr_print(e->right);
        case (EXPR_AND):
            expr_print(e->left);
            printf(" && ");
            expr_print(e->right);
        case (EXPR_OR):
            expr_print(e->left);
            printf(" || ");
            expr_print(e->right);
        case (EXPR_ASSIGNMENT):
            expr_print(e->left);
            printf(" = ");
            expr_print(e->right);
        case (EXPR_BOOLEAN_LITERAL):
            expr_print(e->left);
            printf("%i",e->literal_value);
            expr_print(e->right);
        case (EXPR_INTEGER_LITERAL):
            expr_print(e->left);
            printf("%i",e->literal_value);
            expr_print(e->right);
        case (EXPR_CHARACTER_LITERAL):
            expr_print(e->left);
            printf("%c",e->literal_value);
            expr_print(e->right);
        case (EXPR_STRING_LITERAL):
            expr_print(e->left);
            printf("%s",e->string_literal);
            expr_print(e->right);
        case (EXPR_IDENTIFIER):
            expr_print(e->left);
            printf("%s",e->name);
            expr_print(e->right);
        case (EXPR_PARENTHESES):
            printf("(");
            expr_print(e->left);
            printf(")");
        case (EXPR_FUNCTION_CALL):
            expr_print(e->left);
            printf("(");
            expr_print(e->right);
            printf(")");
        case (EXPR_ARRAY_INDEX):
            expr_print(e->left);
            printf("[");
            expr_print(e->right);
            printf("]");
    }

    if (e->next != 0){
        printf(", "); 
        expr_print(e->next);
    }*/
}
