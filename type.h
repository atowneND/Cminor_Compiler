#ifndef TYPE_H
#define TYPE_H

#include "expr.h"

typedef enum {
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
	TYPE_VOID
} type_kind_t;

struct type {
	type_kind_t kind;
	struct param_list *params;
	struct type *subtype;
	struct expr *expr;
};

struct type * type_create(
    type_kind_t kind,
    struct param_list *params,
    struct type *subtype,
    struct expr *expression
);
void type_print_error( struct type *t );
void type_print( struct type *t );

struct type *type_copy(struct type *t);
int type_compare(struct type *a, struct type *b);
void type_delete(struct type *t);

const char *type_codegen(FILE *fd, struct type *t);

#endif
