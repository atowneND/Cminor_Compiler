#ifndef SCOPE_H
#define SCOPE_H

#include "symbol.h"
#include "hash_table.h"

void scope_enter(void);
void scope_exit(void);
int scope_level(void);
void scope_bind(const char *name, struct symbol *s);
struct symbol *scope_lookup(const char *name);
struct symbol *scope_lookup_local(const char *name);

void sym_table_print(struct hash_table *h);
int sym_is_global(struct decl *d);
#endif
