/*
Declare token types at the top of the bison file,
causing them to be automatically generated in parser.tab.h
for use by scanner.c.
*/

%token TOKEN_ARRAY
%token TOKEN_BOOLEAN
%token TOKEN_CHARACTER
%token TOKEN_ELSE
%token TOKEN_FALSE
%token TOKEN_FOR
%token TOKEN_FCALL
%token TOKEN_IF
%token TOKEN_INTEGER
%token TOKEN_PRINT
%token TOKEN_RETURN
%token TOKEN_STRING
%token TOKEN_TRUE
%token TOKEN_VOID
%token TOKEN_IDENT
%token TOKEN_INTEGER_LITERAL
%token TOKEN_CHARACTER_LITERAL
%token TOKEN_STRING_LITERAL
%token TOKEN_LBRACK
%token TOKEN_RBRACK
%token TOKEN_LBRACE
%token TOKEN_RBRACE
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_INC
%token TOKEN_DEC
%token TOKEN_NEG
%token TOKEN_POW
%token TOKEN_MULT
%token TOKEN_DIV
%token TOKEN_MOD
%token TOKEN_ADD
%token TOKEN_LT
%token TOKEN_LE
%token TOKEN_GT
%token TOKEN_GE
%token TOKEN_EQ_COMP
%token TOKEN_NE_COMP
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_NOT
%token TOKEN_ASSIGN
%token TOKEN_COMMA
%token TOKEN_COLON
%token TOKEN_SC
%token TOKEN_WS
%token TOKEN_CPP_COMMENT
%token TOKEN_C_COMMENT
%token TOKEN_WHILE
%token TOKEN_EOF
%token TOKEN_OTHER

%{

#include <math.h>
#include <stdio.h>
#include "decl.h"
#include "stmt.h"
#include "expr.h"
#include "type.h"
#include "param_list.h"

/*
YYSTYPE is the lexical value returned by each rule in a bison grammar.
By default, it is an integer. In this example, we are returning a pointer to an expression.
*/

#define YYSTYPE struct expr *

/*
Clunky: Manually declare the interface to the scanner generated by flex. 
*/

extern char *yytext;
extern int yylex();
extern int yyerror( char *str );

/*
Clunky: Keep the final result of the parse in a global variable,
so that it can be retrieved by main().
*/

struct expr * parser_result = 0;

%}

%union {
    struct decl *decl;
    struct stmt *statement_node;
    struct expr *expression_node;
    struct type *type_node;
    struct param_list *param_list_node;
    struct symbol *symbol_node;
};

%type<decl_list> decl_list program
%type<stmt_list> stmt_list
/*%type<param_list> param_list non_empty_param_list param*/
%type<expression> optional_expression expression assign_level_expr or_comparison_expr and_comparison_expr eq_comparison_expr value_comparison_expr add_level_expr mult_level_expr exponent_level_expr unary_level_expr base_level_expr ident TOKEN_INTEGER_LITERAL TOKEN_STRING_LITERAL TOKEN_CHARACTER_LITERAL TOKEN_TRUE TOKEN_FALSE

%token END 0 "end of file"

%%

/* Here is the grammar: program is the start symbol. */
program     
    : decl_list
        { $$ = $1; }
    ;

decl_list   
    : decl decl_list
    |
        { $$ = 0; }
    ;

decl
    : ident TOKEN_COLON type TOKEN_ASSIGN expression TOKEN_SC /* other type assingments */
    /*    { $$ = decl_create($1, $3, $5, 0, 0); }
    | ident TOKEN_COLON type TOKEN_SC /* declarations without assignments */
/*    | ident TOKEN_COLON type TOKEN_ASSIGN TOKEN_LBRACE expression_list TOKEN_RBRACE TOKEN_SC /* array assignment */
    | ident TOKEN_COLON type TOKEN_ASSIGN TOKEN_LBRACE stmt_list TOKEN_RBRACE /* function assignments */
    ;

stmt_list
    : stmt_list stmt
    |
        { $$ = 0; }
    ;

stmt
    : decl
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN matched_stmt TOKEN_ELSE stmt
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN stmt
    | return_stmt
    | print_stmt
    | optional_expression TOKEN_SC;
    | TOKEN_LBRACE stmt_list TOKEN_RBRACE
    | TOKEN_FOR TOKEN_LPAREN optional_expression TOKEN_SC optional_expression TOKEN_SC optional_expression TOKEN_RPAREN stmt
    ;

matched_stmt 
    : decl
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN matched_stmt TOKEN_ELSE matched_stmt
    | return_stmt
    | print_stmt
    | optional_expression TOKEN_SC
    | TOKEN_LBRACE stmt_list TOKEN_RBRACE
    | TOKEN_FOR TOKEN_LPAREN optional_expression TOKEN_SC optional_expression TOKEN_SC optional_expression TOKEN_RPAREN matched_stmt
    ;

return_stmt 
    : TOKEN_RETURN optional_expression TOKEN_SC
    ;

print_stmt  
    : TOKEN_PRINT optional_expression_list TOKEN_SC
    ;

type
    : TOKEN_STRING
    | TOKEN_CHARACTER
    | TOKEN_INTEGER
    | TOKEN_BOOLEAN
    | TOKEN_VOID
    | TOKEN_ARRAY TOKEN_LBRACK optional_expression TOKEN_RBRACK type
    | TOKEN_FCALL type TOKEN_LPAREN param_list TOKEN_RPAREN
    ;

param_list
    : non_empty_param_list param
    | param
    |
/*        { $$ = 0; }*/
    ;

non_empty_param_list
    : param TOKEN_COMMA
    | non_empty_param_list param TOKEN_COMMA
    ;

param
    : ident TOKEN_COLON type
    ;

optional_expression
    : 
        { $$ = 0; }
    | expression
    ;

optional_expression_list
    :
    | expression_list
    ;

expression_list
    : non_empty_expr_prefix expression
    | expression
    ;

non_empty_expr_prefix
    : expression TOKEN_COMMA
    | non_empty_expr_prefix expression TOKEN_COMMA
    ;

expression  
    : assign_level_expr
        { $$ = $1; }
    ;
    
assign_level_expr
    : assign_level_expr TOKEN_ASSIGN or_comparison_expr
        { $$ = expr_create(EXPR_ASSIGNMENT, $1, $3); }
    | or_comparison_expr
        { $$ = $1; }
    ;
    
or_comparison_expr
    : or_comparison_expr TOKEN_OR and_comparison_expr
        { $$ = expr_create(EXPR_OR, $1, $3); }
    | and_comparison_expr
        { $$ = $1; }
    ;
    
and_comparison_expr
    : and_comparison_expr TOKEN_AND eq_comparison_expr
        { $$ = expr_create(EXPR_AND, $1, $3); }
    | eq_comparison_expr
        { $$ = $1; }
    ;
    
eq_comparison_expr
    : eq_comparison_expr TOKEN_EQ_COMP value_comparison_expr
        { $$ = expr_create(EXPR_EQUIVALENCE_COMPARISON, $1, $3); }
    | eq_comparison_expr TOKEN_NE_COMP value_comparison_expr
        { $$ = expr_create(EXPR_NONEQUIVALENCE_COMPARISON, $1, $3); }
    | value_comparison_expr
        { $$ = $1; }
    ;

value_comparison_expr
    : value_comparison_expr TOKEN_LT add_level_expr
        { $$ = expr_create(EXPR_LESS_THAN, $1, $3); }
    | value_comparison_expr TOKEN_LE add_level_expr
        { $$ = expr_create(EXPR_LESS_THAN_OR_EQUAL, $1, $3); }
    | value_comparison_expr TOKEN_GT add_level_expr
        { $$ = expr_create(EXPR_GREATER_THAN, $1, $3); }
    | value_comparison_expr TOKEN_GE add_level_expr
        { $$ = expr_create(EXPR_GREATER_THAN_OR_EQUAL, $1, $3); }
    | add_level_expr
        { $$ = $1; }
    ;

add_level_expr
    : add_level_expr TOKEN_ADD mult_level_expr
        { $$ = expr_create(EXPR_ADD, $1, $3); }
    | add_level_expr TOKEN_NEG mult_level_expr
        { $$ = expr_create(EXPR_SUB, $1, $3); }
    | mult_level_expr
        { $$ = $1; }
    ;

mult_level_expr 
    : mult_level_expr TOKEN_MULT base_level_expr
        { $$ = expr_create(EXPR_MULTIPLY, $1, $3); }
    | mult_level_expr TOKEN_DIV base_level_expr
        { $$ = expr_create(EXPR_DIV, $1, $3); }
    | mult_level_expr TOKEN_MOD base_level_expr
        { $$ = expr_create(EXPR_MODULO, $1, $3); }
    | exponent_level_expr
        { $$ = $1; }
    ;

exponent_level_expr
    : exponent_level_expr TOKEN_POW unary_level_expr
        { $$ = expr_create(EXPR_POWER, $1, $3); }
    | unary_level_expr
        { $$ = $1; }
    ;

unary_level_expr
    : TOKEN_NOT base_level_expr
        { $$ = expr_create(EXPR_NOT, 0, $2); }
    | TOKEN_NEG base_level_expr
        { $$ = expr_create(EXPR_SUB, 0, $2); }
    | TOKEN_ADD base_level_expr
        { $$ = expr_create(EXPR_ADD, 0, $2); }
    | base_level_expr
        { $$ = $1; }
    ;

base_level_expr
    : ident
        { $$ = expr_create_name($1); }
    | TOKEN_INTEGER_LITERAL
        { $$ = expr_create_integer_literal($1); }
    | TOKEN_STRING_LITERAL
        { $$ = expr_create_string_literal($1); }
    | TOKEN_CHARACTER_LITERAL
        { $$ = expr_create_character_literal($1); }
    | TOKEN_TRUE
        { $$ = expr_create_boolean_literal($1); }
    | TOKEN_FALSE
        { $$ = expr_create_boolean_literal($1); }
    | TOKEN_LPAREN expression TOKEN_RPAREN
        { $$ = expr_create(EXPR_PARENTHESES, $2, 0); }
    | ident TOKEN_LBRACK expression TOKEN_RBRACK
    | ident TOKEN_LPAREN optional_expression_list TOKEN_RPAREN
    | base_level_expr TOKEN_INC /* is this right? */
        { $$ = expr_create(EXPR_INCREMENT, $1, 0); }
    | base_level_expr TOKEN_DEC /* is this right? */
        { $$ = expr_create(EXPR_DECREMENT, $1, 0); }
    ;

ident       
    : TOKEN_IDENT /* need to add to the symbol table, so this token gets its own NT */
        /* this is not right */
        { $$ = expr_create_name(yytext);}
    ;

%%

/*
This function will be called by bison if the parse should
encounter an error.  In principle, "str" will contain something
useful.  In practice, it often does not.
*/

int yyerror( char *str )
{
	printf("parse error: %s\n",str);
	return -1;
}
