#include "stmt.h"
#include <stdlib.h>

extern int indent;

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

void stmt_print( struct stmt *s ) {
//    printf("%i, idents=%i\n",s->kind,indent);
    if (s != NULL) {
        switch (s->kind){
            case STMT_DECL:
                print_indents();
                decl_print(s->decl);
                break;
            case STMT_EXPR:
                print_indents();
                expr_print(s->init_expr);
                printf(";\n");
                break;
            case STMT_IF_ELSE:
                print_indents();
                printf("if (");
                expr_print(s->init_expr);
                if (s->body->kind== STMT_BLOCK) {
                    printf(") \n");
                    stmt_print(s->body);
                }else{
                    printf(")\n");
                    print_indents();
                    printf("{\n");
                    indent += 1;
                    stmt_print(s->body);
                    indent -= 1;
                }

                if (s->else_body != 0) {
                    print_indents();
                    printf("else\n");

                    stmt_print(s->else_body);

                    print_indents();
                    printf("\n");

                } else {
                    print_indents();
                    printf("}\n");
                }

                break;
            case STMT_FOR:
                print_indents();
                printf("for (");
                expr_print(s->init_expr);
                printf("; ");
                expr_print(s->expr);
                printf("; ");
                expr_print(s->next_expr);
                printf(")\n");
                
                stmt_print(s->body);
                printf("\n");

                break;
            case STMT_PRINT:
                print_indents();
                printf("print ");
                expr_print(s->init_expr);
                printf(";\n");

                break;
            case STMT_RETURN:
                print_indents();
                printf("return ");
                expr_print(s->init_expr);
                printf(";\n");

                break;
            case STMT_BLOCK:
                print_indents();
                printf("{\n");

                indent += 1;
                stmt_print(s->body);

                indent -= 1;
                print_indents();
                printf("}\n");
                break;

            case STMT_WHILE:
                fprintf(stderr,"While loops not accepted.\n");
                break;
        }
        if (s->next != NULL){
            stmt_print(s->next);
        }
    }
}

void print_indents(void){
    int i;
    for (i=0; i<indent; i++){
        printf("    ");
    }
}

void stmt_resolve( struct stmt *s ){
    if (s != NULL) {
        // resolve this stmt
        switch (s->kind){
            case STMT_DECL:
                decl_resolve(s->decl);
                break;
            case STMT_EXPR:
                break;
            case STMT_IF_ELSE:
                break;
            case STMT_FOR:
                break;
            case STMT_WHILE:
                break;
            case STMT_PRINT:
                break;
            case STMT_RETURN:
                break;
            case STMT_BLOCK:
                break;
            default:
                break;
        }
        // add to symbol table
        if (s->next != NULL) {
            stmt_resolve(s->next);
        }
    }
}
