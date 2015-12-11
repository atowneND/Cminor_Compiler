#include <stdlib.h>
#include "type.h"
#include "scope.h"
#include "stmt.h"
#include "reg.h"
#include "param_list.h"

extern int indent;
extern int error_counter;
extern int condition_counter;

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

void stmt_typecheck(struct stmt *s, struct type *current_type, struct decl *d){
    if (s == NULL){
        return;
    }

    type_kind_t expected_return_type;
    type_kind_t return_type;
    struct expr *e = malloc(sizeof(struct expr));

    switch (s->kind){
	    case STMT_DECL:
	        decl_typecheck(s->decl);
	        break;
	    case STMT_EXPR:
	        s->init_expr->type = expr_typecheck(s->init_expr,d);
	        break;
	    case STMT_IF_ELSE:
	        s->init_expr->type = expr_typecheck(s->init_expr,d);
	        if (s->init_expr != NULL){
	            if (s->init_expr->type != NULL) {
                    if (s->init_expr->type->kind != TYPE_BOOLEAN){
                        error_counter += 1;
                        fprintf(stderr,"Error #%i ",error_counter);
                        fprintf(stderr,"type error: expression in if statement must be boolean: ");
                        expr_print_error(s->init_expr);
                        fprintf(stderr,"\n");
                    }
                    stmt_typecheck(s->body,current_type,d);
                    stmt_typecheck(s->else_body,current_type,d);
                }
            }
	        break;
	    case STMT_FOR:
	        s->init_expr->type = expr_typecheck(s->init_expr,d);
	        s->expr->type = expr_typecheck(s->expr,d);
	        s->next_expr->type = expr_typecheck(s->next_expr,d);
	        stmt_typecheck(s->body,current_type,d);
	        break;
        case STMT_WHILE:
            // this should never happen. I just want gcc -Wall to be quiet about it
            break;
	    case STMT_PRINT:
	        e = s->init_expr;
	        while (e != NULL) { 
	            e->type = expr_typecheck(e,d);
	            e = e->next;
            }
	        break;
	    case STMT_RETURN:
	        if (s->init_expr != NULL) { 
	            s->init_expr->type = expr_typecheck(s->init_expr,d);

                return_type = s->init_expr->type->kind;
            } else {
                return_type = TYPE_VOID;
            }
            
            if (current_type->kind == TYPE_FUNCTION){
                expected_return_type = current_type->subtype->kind;
            } else {
                expected_return_type = current_type->kind;
            }

            if (return_type != expected_return_type){
                error_counter += 1;
                fprintf(stderr,"Error #%i ",error_counter);
                fprintf(stderr,"type error: returned expression has type ");
                if (s->init_expr!=NULL){ 
                    expr_print_error(s->init_expr);
                } else {
                    fprintf(stderr,"void");
                }
                if (s->init_expr!=NULL){ 
                    if (s->init_expr->type!=NULL){ 
                        type_print_error(s->init_expr->type);
                    } else {
                        fprintf(stderr,"void");
                    }
                }
                fprintf(stderr,"\n\tFunction expecting return type ");
                type_print_error(current_type);
                fprintf(stderr,"\n");
            }

	        break;
        case STMT_BLOCK:
            stmt_typecheck(s->body,current_type,d);
            break;
    }
    stmt_typecheck(s->next, current_type,d);
}

void stmt_codegen(struct stmt *s, FILE *fd){
    if (!s) return;
    struct expr *e = malloc(sizeof(struct expr));
    switch (s->kind){
        case STMT_DECL:
            decl_codegen(s->decl,fd);
            break;
        case STMT_EXPR:
            expr_codegen(s->init_expr,fd);
            break;
        case STMT_IF_ELSE:
            expr_codegen(s->init_expr,fd);
            fprintf(fd,"# IF STATEMENT\n");
            fprintf(fd,"    cmpq $1, %s\n",register_name(s->init_expr->reg));
            fprintf(fd,"    je cond%i\n",condition_counter);
            stmt_codegen(s->else_body,fd);
            fprintf(fd,"    jmp done%i\n",condition_counter);

            fprintf(fd,"# if (true)\n");
            fprintf(fd,"cond%i:\n",condition_counter);
            stmt_codegen(s->body,fd);

            fprintf(fd,"# false or continue\n");
            fprintf(fd,"done%i:\n",condition_counter);

            condition_counter += 1;
            break;
        case STMT_FOR:
            expr_codegen(s->init_expr,fd); // evaluate first expression in for parens
            // L1
            expr_codegen(s->expr,fd); // proceed?
            // CMP %E, $0
            stmt_codegen(s->body,fd); // if yes, evaluate body of for loop
            expr_codegen(s->next_expr,fd); // iterate
            // JMP L1
            // L2
            break;
        case STMT_WHILE:
            fprintf(stderr,"while loops not supported\n");
            break;
        case STMT_PRINT:
            e = s->init_expr;
            while (e != NULL) {
                switch (e->type->kind){
                    case TYPE_BOOLEAN:
                        // call print_boolean(int b);
                        break;
                    case TYPE_CHARACTER:
                        // call print_character(char c);
                        break;
                    case TYPE_INTEGER:
                        expr_codegen(e,fd);
                        fprintf(fd,"    pushq %s # save argument on the stack\n",register_name(e->reg));
                        fprintf(fd,"    call print_integer\n");
                        // call print_integer(int x);
                        break;
                    case TYPE_STRING:
                        // call print_string(const char *s);
                        break;
                    case TYPE_ARRAY:
                        fprintf(stderr,"arrays are not supported\n");
                        break;
                    case TYPE_FUNCTION:
                        // fprintf(fd,".data\n");
                        // preamble
                        // call function
                        // need to include parameter list
                        // postamble
                        break;
                    case TYPE_VOID:
                        // wtf do you do with a void?
                        break;
                }
                e = e->next;
            }
            // determine type
            // switch case and print
            break;
        case STMT_RETURN:
            expr_codegen(s->init_expr,fd); // puts reduced expression in %rax
            fprintf(fd,"    # RETURN VALUE\n");
            fprintf(fd,"    mov %s, %%rax\n",register_name(s->init_expr->reg));
            print_postamble(fd);
            break;
        case STMT_BLOCK:
            stmt_codegen(s->body,fd);
            break;
    }
    stmt_codegen(s->next, fd);
}

void print_preamble(FILE *fd, struct decl *d){
    fprintf(fd,"    # PREAMBLE\n");
    
    // set base and stack pointers
    fprintf(fd,"    pushq %%rbp # save the base pointer\n");
    fprintf(fd,"    mov %%rsp, %%rbp # set a new base pointer\n");

    // arguments
    param_codegen_push(d->type->params, fd);
    register_free_type(ARGUMENT);

    // local variables
    fprintf(fd,"    subq $16, %%rsp\n"); // TODO change this to allocate number of local variables

    // save registers
    fprintf(fd,"    pushq %%rbx # save callee saved registers\n");
    fprintf(fd,"    pushq %%r12\n");
    fprintf(fd,"    pushq %%r13\n");
    fprintf(fd,"    pushq %%r14\n");
    fprintf(fd,"    pushq %%r15\n");
}

void print_postamble(FILE *fd){
    fprintf(fd,"    # POSTAMBLE\n");
    fprintf(fd,"    popq %%r15 # restore callee saved registers\n");
    fprintf(fd,"    popq %%r14\n");
    fprintf(fd,"    popq %%r13\n");
    fprintf(fd,"    popq %%r12\n");
    fprintf(fd,"    popq %%rbx\n");
    fprintf(fd,"    mov %%rbp, %%rsp # reset stack to previous base pointer\n");
    fprintf(fd,"    popq %%rbp # recover previous base pointer\n");
    fprintf(fd,"    ret # return to the caller\n");
}
