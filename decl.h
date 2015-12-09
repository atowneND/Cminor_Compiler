#ifndef DECL_H
#define DECL_H

#include "decl.h"
#include "type.h"
#include "stmt.h"
#include "expr.h"
#include <stdio.h>

struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
};

struct decl * decl_create( 
        char *name,
        struct type *t,
        struct expr *v,
        struct stmt *c,
        struct decl *next 
);
void decl_print( struct decl *d );

void decl_resolve( struct decl *d );
struct type *decl_typecheck(struct decl *d);
int decl_expr_comp(struct decl *d);

void decl_codegen(struct decl *d, FILE *fd);

#endif
