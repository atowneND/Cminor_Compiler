#ifndef STMT_H
#define STMT_H

#include "type.h"
#include "decl.h"

struct type;

typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_WHILE,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK
} stmt_kind_t;

struct stmt {
	stmt_kind_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt * stmt_create( stmt_kind_t kind, struct decl *d, struct expr *init_expr, struct expr *e, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next );
void print_indents(void);
void stmt_print( struct stmt *s );

void stmt_resolve( struct stmt *s );
void stmt_typecheck(struct stmt *s, struct type *current_type);

#endif
