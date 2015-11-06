#include "stmt.h"
#include <stdlib.h>

struct stmt * stmt_create(
        stmt_kind_t kind,
        struct decl *d,
        struct expr *init_expr,
        struct expr *e,
        struct expr *next_expr,
        struct stmt *body,
        struct stmt *else_body,
        struct stmt *next 
    ){
    // create new struct
    struct stmt *new_stmt = malloc(sizeof(struct stmt));

    new_stmt->kind = kind;
    new_stmt->decl = d;
    new_stmt->init_expr = init_expr;
    new_stmt->expr = e;
    new_stmt->next_expr = next_expr;
    new_stmt->body = body;
    new_stmt->else_body = else_body;
    new_stmt->next = next;

    return new_stmt;
}

void stmt_print( struct stmt *s, int indent ) {
    if (s != NULL) {
        switch (s->kind){
            case STMT_DECL:
                decl_print(s->decl, indent);
                break;
            case STMT_EXPR:
                expr_print(s->init_expr);
                break;
            case STMT_IF_ELSE:
                print_indents(indent);
                printf("if (");
                expr_print(s->init_expr);
                printf(") {\n");

                indent += 1;
                stmt_print(s->body, indent);
                indent = indent - 1;

                if (s->else_body != 0) {
                    print_indents(indent);
                    printf("} else {\n");

                    indent = indent + 1;
                    stmt_print(s->else_body, indent);

                    indent = indent - 1;
                    print_indents(indent);
                    printf("}\n");

                } else {
                    print_indents(indent);
                    printf("}\n");
                }

                break;
            case STMT_FOR:
                print_indents(indent);
                printf("for (");
                expr_print(s->init_expr);
                printf("; ");
                expr_print(s->expr);
                printf("; ");
                expr_print(s->next_expr);
                printf(") {\n");
                
                indent = indent + 1;
                stmt_print(s->body, indent);

                indent = indent - 1;
                print_indents(indent);
                printf("}\n");

                break;
            case STMT_PRINT:
                print_indents(indent);
                printf("print ");
                expr_print(s->init_expr);
                printf(";\n");

                break;
            case STMT_RETURN:
                print_indents(indent);
                printf("return ");
                expr_print(s->init_expr);
                printf(";\n");

                break;
            case STMT_BLOCK:
                print_indents(indent);
                printf("{\n");

                indent = indent + 1;
                stmt_print(s->body, indent);

                indent = indent - 1;
                print_indents(indent);
                printf("}\n");
                break;

            case STMT_WHILE:
                fprintf(stderr,"While loops not accepted.\n");
                break;
        }
    }
}

void print_indents(int indent){
    int i;
    for (i=0; i<indent; i++){
        printf("    ");
    }
}
