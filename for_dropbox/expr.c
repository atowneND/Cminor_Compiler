#include "expr.h"
#include <stdlib.h>

extern int indent;

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
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = EXPR_IDENTIFIER;
    new_expression->name = n;
    
    return new_expression;
}

struct expr * expr_create_boolean_literal( int c ){
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = EXPR_BOOLEAN_LITERAL;
    new_expression->literal_value = c;

    return new_expression;
}

struct expr * expr_create_integer_literal( int c ){
    struct expr *new_expression = malloc(sizeof(struct expr));

    new_expression->kind = EXPR_INTEGER_LITERAL;
    new_expression->literal_value = c;

    return new_expression;
}

struct expr * expr_create_character_literal( int c ){
    struct expr *new_expression = malloc(sizeof(struct expr));
    
    new_expression->kind = EXPR_CHARACTER_LITERAL;
    new_expression->literal_value = c;

    return new_expression;
}

struct expr * expr_create_string_literal( const char *str ){
    struct expr *new_expression = malloc(sizeof(struct expr));
    
    new_expression->kind = EXPR_STRING_LITERAL;
    new_expression->string_literal = str;

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
                printf("[");
                if (e->right != 0) expr_print(e->right);
                printf("]");
                break;
        }
        if (e->next != NULL){
            printf(", "); 
            expr_print(e->next);
        }
    }

}