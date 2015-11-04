#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"

typedef enum {
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_INCREMENT,
	EXPR_DECREMENT,
	EXPR_NOT,
	EXPR_POWER,
	EXPR_MODULO,
	EXPR_LESS_THAN,
	EXPR_GREATER_THAN,
	EXPR_LESS_THAN_OR_EQUAL,
	EXPR_GREATER_THAN_OR_EQUAL,
	EXPR_EQUIVALENCE_COMPARISON,
    EXPR_NONEQUIVALENCE_COMPARISON,
    EXPR_AND,
    EXPR_OR,
    EXPR_ASSIGNMENT,
    EXPR_BOOLEAN_LITERAL,
    EXPR_INTEGER_LITERAL,
    EXPR_CHARACTER_LITERAL,
    EXPR_STRING_LITERAL,
    EXPR_IDENTIFIER,
	/* many more types to add here */
} expr_t;

struct expr {
	/* used by all expr types */
	expr_t kind;
	struct expr *left;
	struct expr *right;

	/* used by leaf expr types */
	const char *name;
	struct symbol *symbol;
	int literal_value;
	const char * string_literal;
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_character_literal( int c );
struct expr * expr_create_string_literal( const char *str );

void expr_print( struct expr *e );

#endif
