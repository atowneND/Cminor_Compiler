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
#include <string.h>
#include <stdlib.h>
#include "decl.h"
#include "stmt.h"
#include "expr.h"
#include "type.h"
#include "param_list.h"

/*
YYSTYPE is the lexical value returned by each rule in a bison grammar.
By default, it is an integer. In this example, we are returning a pointer to an expression.
*/

/*#define YYSTYPE struct expr */

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
struct decl *ast_pointer;

%}

%union {
    struct decl *decl;
    struct stmt *stmt;
    struct expr *expr;
    struct type *type;
    struct param_list *param_list;
    struct symbol *symbol;
    char *str_literal;
    int int_literal;
};

%type <decl> program decl_list decl
%type <stmt> stmt_list stmt matched_stmt return_stmt print_stmt
%type <param_list> param_list non_empty_param_list param
%type <expr> index_list array_list array_index array_size optional_expression optional_expression_list non_empty_expr_prefix expression_list expression assign_level_expr or_comparison_expr and_comparison_expr eq_comparison_expr value_comparison_expr add_level_expr mult_level_expr exponent_level_expr unary_level_expr base_level_expr
%type <type> type
%type <str_literal> ident string_literal
%type <int_literal> integer_literal character_literal true_literal false_literal

%token END 0 "end of file"

%%

/* Here is the grammar: program is the start symbol. */
program     
    : decl_list
        { ast_pointer = $1; }
    ;

decl_list   
    : decl decl_list
        { $$->next = $1; $1->next = $2; }
    |
        { $$ = 0; }
    ;

decl
    : ident TOKEN_COLON type TOKEN_ASSIGN expression TOKEN_SC /* other type assingments */
        { $$ = decl_create($1, $3, $5, 0, 0); }
    | ident TOKEN_COLON type TOKEN_SC /* declarations without assignments */
        { $$ = decl_create($1, $3, 0, 0, 0); }
    | ident TOKEN_COLON type TOKEN_ASSIGN TOKEN_LBRACE expression_list TOKEN_RBRACE TOKEN_SC /* array assignment */
        { $$ = decl_create($1, $3, $6, 0, 0); }
    | ident TOKEN_COLON type TOKEN_ASSIGN TOKEN_LBRACE stmt_list TOKEN_RBRACE /* function assignments */
        { $$ = decl_create($1, $3, 0, $6, 0); }
    ;

stmt_list
    : stmt stmt_list
        { $$ = $1; $1->next = $2; }
    |
        { $$ = 0; }
    ;

stmt
    : decl
        { $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0); } 
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN matched_stmt TOKEN_ELSE stmt
        { $$ = stmt_create(STMT_IF_ELSE, 0, $3, 0, 0, $5, $7, 0); }
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN stmt
        { $$ = stmt_create(STMT_IF_ELSE, 0, $3, 0, 0, $5, 0, 0); }
    | return_stmt
        { $$ = $1; }
    | print_stmt
        { $$ = $1; }
    | expression TOKEN_SC
        { $$ = stmt_create(STMT_EXPR, 0, $1, 0, 0, 0, 0, 0); }
    | TOKEN_LBRACE stmt_list TOKEN_RBRACE
        { $$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0, 0); }
    | TOKEN_FOR TOKEN_LPAREN optional_expression TOKEN_SC optional_expression TOKEN_SC optional_expression TOKEN_RPAREN stmt
        { $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0, 0); }
    ;

matched_stmt 
    : decl
        { $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0); } 
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN matched_stmt TOKEN_ELSE matched_stmt
        { $$ = stmt_create(STMT_IF_ELSE, 0, $3, 0, 0, $5, $7, 0); }
    | return_stmt
        { $$ = $1; }
    | print_stmt
        { $$ = $1; }
    | expression TOKEN_SC
        { $$ = stmt_create(STMT_EXPR, 0, $1, 0, 0, 0, 0, 0); }
    | TOKEN_LBRACE stmt_list TOKEN_RBRACE
        { $$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0, 0); }
    | TOKEN_FOR TOKEN_LPAREN optional_expression TOKEN_SC optional_expression TOKEN_SC optional_expression TOKEN_RPAREN matched_stmt
        { $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0, 0); }
    ;

return_stmt 
    : TOKEN_RETURN optional_expression TOKEN_SC
        { $$ = stmt_create(STMT_RETURN, 0, $2, 0, 0, 0, 0, 0); }
    ;

print_stmt  
    : TOKEN_PRINT optional_expression_list TOKEN_SC
        { $$ = stmt_create(STMT_PRINT, 0, $2, 0, 0, 0, 0, 0); }
    ;

type
    : TOKEN_STRING
        { $$ = type_create(TYPE_STRING, 0, 0, 0); }
    | TOKEN_CHARACTER
        { $$ = type_create(TYPE_CHARACTER, 0, 0, 0); }
    | TOKEN_INTEGER
        { $$ = type_create(TYPE_INTEGER, 0, 0, 0); }
    | TOKEN_BOOLEAN
        { $$ = type_create(TYPE_BOOLEAN, 0, 0, 0); }
    | TOKEN_VOID
        { $$ = type_create(TYPE_VOID, 0, 0, 0); }
    | TOKEN_ARRAY array_size type
        { $$ = type_create(TYPE_ARRAY, 0, $3, $2); }
    | TOKEN_FCALL type TOKEN_LPAREN param_list TOKEN_RPAREN
        { $$ = type_create(TYPE_FUNCTION, $4, $2, 0); }
    ;

array_size
    : TOKEN_LBRACK optional_expression TOKEN_RBRACK array_size
        { $$ = $2; if ($2 != 0) {$2->next_array_dimension = $4;} }
    |
        { $$ = 0; }
    ;

param_list
    : non_empty_param_list param
        { $$ = $1; param_list_append($1, $2); }
    | param
        { $$ = $1; }
    |
        { $$ = 0; }
    ;

non_empty_param_list
    : param TOKEN_COMMA
        { $$ = $1; }
    | non_empty_param_list param TOKEN_COMMA
        { $$ = $1; param_list_append($1, $2); }
    ;

param
    : ident TOKEN_COLON type
        { $$ = param_list_create( $1, $3, 0); }
    ;

optional_expression
    : 
        { $$ = 0; }
    | expression
        { $$ = $1; }
    ;

optional_expression_list
    :
        { $$ = 0; }
    | expression_list
        { $$ = $1; }
    ;

expression_list
    : non_empty_expr_prefix expression
        { $$ = $1; expr_append($1, $2); }
    | expression
        { $$ = $1; }
    ;

non_empty_expr_prefix
    : expression TOKEN_COMMA
        { $$ = $1; } 
    | non_empty_expr_prefix expression TOKEN_COMMA
        { $$ = $1; expr_append($1, $2); }
    ;

expression  
    : assign_level_expr
        { $$ = $1; }
    ;
    
assign_level_expr
/* maybe add ARRAY ASSIGNMENT here? */
    : assign_level_expr TOKEN_ASSIGN or_comparison_expr
        { $$ = expr_create(EXPR_ASSIGNMENT, $1, $3, 0); }
    | assign_level_expr TOKEN_ASSIGN array_list
        { $$ = expr_create(EXPR_ASSIGNMENT, $1, $3, 0); }
    | or_comparison_expr
        { $$ = $1; }
    ;

array_list
    : TOKEN_LBRACE expression_list TOKEN_RBRACE
        { $$ = $2; }
    ;
    
or_comparison_expr
    : or_comparison_expr TOKEN_OR and_comparison_expr
        { $$ = expr_create(EXPR_OR, $1, $3, 0); }
    | and_comparison_expr
        { $$ = $1; }
    ;
    
and_comparison_expr
    : and_comparison_expr TOKEN_AND eq_comparison_expr
        { $$ = expr_create(EXPR_AND, $1, $3, 0); }
    | eq_comparison_expr
        { $$ = $1; }
    ;
    
eq_comparison_expr
    : eq_comparison_expr TOKEN_EQ_COMP value_comparison_expr
        { $$ = expr_create(EXPR_EQUIVALENCE_COMPARISON, $1, $3, 0); }
    | eq_comparison_expr TOKEN_NE_COMP value_comparison_expr
        { $$ = expr_create(EXPR_NONEQUIVALENCE_COMPARISON, $1, $3, 0); }
    | value_comparison_expr
        { $$ = $1; }
    ;

value_comparison_expr
    : value_comparison_expr TOKEN_LT add_level_expr
        { $$ = expr_create(EXPR_LESS_THAN, $1, $3, 0); }
    | value_comparison_expr TOKEN_LE add_level_expr
        { $$ = expr_create(EXPR_LESS_THAN_OR_EQUAL, $1, $3, 0); }
    | value_comparison_expr TOKEN_GT add_level_expr
        { $$ = expr_create(EXPR_GREATER_THAN, $1, $3, 0); }
    | value_comparison_expr TOKEN_GE add_level_expr
        { $$ = expr_create(EXPR_GREATER_THAN_OR_EQUAL, $1, $3, 0); }
    | add_level_expr
        { $$ = $1; }
    ;

add_level_expr
    : add_level_expr TOKEN_ADD mult_level_expr
        { $$ = expr_create(EXPR_ADD, $1, $3, 0); }
    | add_level_expr TOKEN_NEG mult_level_expr
        { $$ = expr_create(EXPR_SUB, $1, $3, 0); }
    | mult_level_expr
        { $$ = $1; }
    ;

mult_level_expr 
    : mult_level_expr TOKEN_MULT exponent_level_expr
        { $$ = expr_create(EXPR_MUL, $1, $3, 0); }
    | mult_level_expr TOKEN_DIV exponent_level_expr
        { $$ = expr_create(EXPR_DIV, $1, $3, 0); }
    | mult_level_expr TOKEN_MOD exponent_level_expr
        { $$ = expr_create(EXPR_MODULO, $1, $3, 0); }
    | exponent_level_expr
        { $$ = $1; }
    ;

exponent_level_expr
    : exponent_level_expr TOKEN_POW unary_level_expr
        { $$ = expr_create(EXPR_POWER, $1, $3, 0); }
    | unary_level_expr
        { $$ = $1; }
    ;

unary_level_expr
    : TOKEN_NOT base_level_expr
        { $$ = expr_create(EXPR_NOT, 0, $2, 0); }
    | TOKEN_NEG base_level_expr
        { $$ = expr_create(EXPR_SUB, 0, $2, 0); }
    | TOKEN_ADD base_level_expr
        { $$ = expr_create(EXPR_ADD, 0, $2, 0); }
    | base_level_expr
        { $$ = $1; }
    ;

base_level_expr
    : ident
        { $$ = expr_create_name($1); }
    | integer_literal 
        { $$ = expr_create_integer_literal($1); }
    | string_literal
        { $$ = expr_create_string_literal($1); }
    | character_literal
        { $$ = expr_create_character_literal($1); }
    | true_literal
        { $$ = expr_create_boolean_literal($1); }
    | false_literal
        { $$ = expr_create_boolean_literal($1); }
    | TOKEN_LPAREN expression TOKEN_RPAREN
        { $$ = expr_create(EXPR_PARENTHESES, $2, 0, 0); }
    | ident index_list 
        { $$ = expr_create(EXPR_ARRAY_INDEX, expr_create_name($1), $2, 0); }
    | ident TOKEN_LPAREN optional_expression_list TOKEN_RPAREN
        { $$ = expr_create(EXPR_FUNCTION_CALL, expr_create_name($1), $3, 0); }
    | base_level_expr TOKEN_INC /* is this right? */
        { $$ = expr_create(EXPR_INCREMENT, $1, 0, 0); }
    | base_level_expr TOKEN_DEC /* is this right? */
        { $$ = expr_create(EXPR_DECREMENT, $1, 0, 0); }
    ;

index_list
    : array_index
        { $$ = $1; }
    | array_index index_list
        { $$ = $2; if ($2 != 0) {$2->next_array_dimension = $1;} }
    ;

array_index
    : TOKEN_LBRACK optional_expression TOKEN_RBRACK
        { $$ = $2; }
    ;


ident       
    : TOKEN_IDENT /* need to add to the symbol table, so this token gets its own NT */
        { $$ = strdup(yytext); }
    ;

integer_literal
    : TOKEN_INTEGER_LITERAL
        { $$ = atoi(yytext); }
    ;

string_literal
    : TOKEN_STRING_LITERAL
        { $$ = strdup(yytext); }
    ;

character_literal
    : TOKEN_CHARACTER_LITERAL
        { $$ = (int)yytext[1]; }
    ;

true_literal
    : TOKEN_TRUE
        { $$ = 1; } 
    ;

false_literal
    : TOKEN_FALSE
        { $$ = 0; }
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
	exit(1);
}
