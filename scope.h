#ifndef SCOPE_H
#define SCOPE_H

#include "hash_table.h"
typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

struct symbol {
	symbol_t kind;
	int which;
	struct type *type;
	char *name;
	struct expr *value;
	struct hash_table_node *function_hash_table;
};

void scope_enter(void);
void scope_exit(void);
int scope_level(void);
void scope_bind(const char *name, struct symbol *s);
struct symbol *scope_lookup(const char *name);
struct symbol *scope_lookup_function(const char *name, struct hash_table_node *ht);
struct symbol *scope_lookup_local(const char *name);

void sym_table_print(struct hash_table *h);
struct symbol *symbol_create(symbol_t kind, struct type *type, char *name, void *value);

char *symbol_code(struct symbol *s,FILE *fd);

#endif
