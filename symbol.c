#include "symbol.h"
#include "decl.h"
#include <stdlib.h>

extern int scope_ctr;
extern int global_ctr;
extern int local_ctr;
extern int param_ctr;

struct symbol *symbol_create(symbol_t kind, struct type *type, char *name){
    struct symbol *sym = malloc(sizeof(struct symbol));
    switch (kind){
        case SYMBOL_GLOBAL:
            sym->which = global_ctr;
            global_ctr += 1;
            break;
        case SYMBOL_LOCAL:
            sym->which = local_ctr;
            local_ctr += 1;
            break;
        case SYMBOL_PARAM:
            sym->which = param_ctr;
            param_ctr += 1;
            break;
    }
    sym->kind = kind;
    sym->type = type;
    sym->name = name;

    return sym;
}

