#include "stmt.h"
#include <stdlib.h>

struct stmt * stmt_create( stmt_kind_t kind, struct decl *d, struct expr *init_expr, struct expr *e, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next ){
    // create new struct
    struct stmt * new_stmt = malloc(sizeof(struct stmt *));
    new_stmt->kind = kind;
    new_stmt->decl = d;
    new_stmt->init_expr = init_expr;
    new_stmt->expr = e;
    new_stmt->next_expr = next_expr;
    new_stmt->body = body;
    new_stmt->else_body = else_body;
    new_stmt->next = next;

    // recurse to next

    return new_stmt;
}

void stmt_print( struct stmt *s, int indent );
