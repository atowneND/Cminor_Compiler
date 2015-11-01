#include "expr.h"

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ){
}

struct expr * expr_create_name( const char *n ){
}
struct expr * expr_create_boolean_literal( int c ){
}
struct expr * expr_create_integer_literal( int c ){
}
struct expr * expr_create_character_literal( int c ){
}
struct expr * expr_create_string_literal( const char *str ){
}

void expr_print( struct expr *e ){
}

