
#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include <stdio.h>

struct expr;
struct type;
struct decl;

struct param_list {
	char *name;
	struct type *type;
	struct symbol *symbol;
	struct param_list *next;
};

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next );
void param_list_append( struct param_list *original_params, struct param_list *new_param);
void param_list_print( struct param_list *a );
void param_list_resolve(struct param_list *p);
void param_list_typecheck(const char *fname,struct expr *e_params,struct decl *d);

#endif
