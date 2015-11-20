#include "type.h"
#include "scope.h"
#include "stmt.h"
#include <stdlib.h>

extern int indent;
extern int error_counter;

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
    if (s == NULL) {
        return;
    }

    // resolve this stmt
    switch (s->kind){
        case STMT_DECL:
            decl_resolve(s->decl);
            break;
        case STMT_EXPR:
            expr_resolve(s->init_expr);
            break;
        case STMT_IF_ELSE:
            expr_resolve(s->init_expr);
            stmt_resolve(s->body);
            stmt_resolve(s->else_body);
            break;
        case STMT_FOR:
            expr_resolve(s->init_expr);
            expr_resolve(s->expr);
            expr_resolve(s->next_expr);
            stmt_resolve(s->body);
            break;
        case STMT_WHILE:
            fprintf(stderr,"While loops not supported\n");
            error_counter += 1;
            break;
        case STMT_PRINT:
            expr_resolve(s->init_expr);
            break;
        case STMT_RETURN:
            expr_resolve(s->init_expr);
            break;
        case STMT_BLOCK:
            scope_enter();
            stmt_resolve(s->body);
            scope_exit();
            break;
        default:
            break;
    }

    // next statement
    if (s->next != NULL) {
        stmt_resolve(s->next);
    }
}

void stmt_typecheck(struct stmt *s, struct type *current_type){
    if (s == NULL){
        return;
    }
    struct type *t = malloc(sizeof(struct type));
    struct expr *e = malloc(sizeof(struct expr));
    switch (s->kind){
	    case STMT_DECL:
	        break;
	    case STMT_EXPR:
	        break;
	    case STMT_IF_ELSE:
	        t = expr_typecheck(s->init_expr);
	        if (t->kind != TYPE_BOOLEAN){
	            error_counter += 1;
	            printf("Error #%i ",error_counter);
	            printf("type error: expression in if statement must be boolean: ");
	            expr_print(s->init_expr);
            }
            stmt_typecheck(s->body,current_type);
            stmt_typecheck(s->else_body,current_type);
	        break;
	    case STMT_FOR:
	        expr_typecheck(s->init_expr);
	        expr_typecheck(s->expr);
	        expr_typecheck(s->next_expr);
	        stmt_typecheck(s->body,current_type);
	        break;
        case STMT_WHILE:
            // this should never happen. I just want gcc -Wall to be quiet about it
            break;
	    case STMT_PRINT:
	        e = s->init_expr;
	        while (e != NULL) { 
	            expr_typecheck(e);
	            e = e->next;
            }
	        break;
	    case STMT_RETURN:
	        t = expr_typecheck(s->init_expr);
	        if (t->kind != current_type->kind){
	            error_counter += 1;
	            printf("Error #%i ",error_counter);
	            printf("type error: returned expression ");
	            expr_print(s->init_expr);
	            printf(" has type ");
	            type_print(t);
	            printf("\n\tFunction expecting return type ");
	            type_print(current_type);
            }
	        break;
        case STMT_BLOCK:
            stmt_typecheck(s->body,current_type);
            break;
    }
    stmt_typecheck(s->next, current_type);
}
