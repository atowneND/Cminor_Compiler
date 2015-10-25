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
%token TOKEN_WHILE
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
%token TOKEN_ASSIGN
%token TOKEN_CPP_COMMENT
%token TOKEN_C_COMMENT
%token TOKEN_COMMA
%token TOKEN_COLON
%token TOKEN_SC
%token TOKEN_WS
%token TOKEN_OTHER
%token TOKEN_EOF

%{

#include <math.h>
#include <stdio.h>
/*#include "expr.h"*/

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

%%

/* Here is the grammar: program is the start symbol. */
program     : decl_list
    ;

decl_list   : decl_list decl
    |
    ;

decl        : ident TOKEN_COLON TOKEN_ASSIGN TOKEN_LBRACE stmt_list TOKEN_RBRACE
    | ident TOKEN_COLON type TOKEN_SC
    | ident TOKEN_COLON type TOKEN_ASSIGN TOKEN_LBRACE stmt_list TOKEN_RBRACE
    ;

type        : TOKEN_STRING
    | TOKEN_CHARACTER
    | TOKEN_INTEGER
    | TOKEN_BOOLEAN
    | TOKEN_VOID
    | TOKEN_ARRAY TOKEN_LBRACK optional_expression TOKEN_RBRACK type
    | TOKEN_FCALL type TOKEN_LPAREN param_list TOKEN_RPAREN
    ;

stmt_list   : stmt
    | stmt_list stmt
    ;

stmt        : TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN matched_stmt TOKEN_ELSE stmt
    | TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN stmt
    | decl
    | print_stmt
    | expression TOKEN_SC
    | return_stmt
    | TOKEN_FOR TOKEN_LPAREN expression TOKEN_SC expression TOKEN_SC expression TOKEN_RPAREN stmt
    | TOKEN_LBRACE stmt_list TOKEN_RBRACE
    ;

matched_stmt : TOKEN_IF TOKEN_LPAREN expression TOKEN_RPAREN matched_stmt TOKEN_ELSE matched_stmt
    | decl
    | return_stmt
    | print_stmt
    | expression TOKEN_SC
    | TOKEN_FOR TOKEN_LPAREN expression TOKEN_SC expression TOKEN_SC expression TOKEN_RPAREN matched_stmt
    | TOKEN_LBRACE stmt_list TOKEN_RBRACE
    ;

return_stmt : TOKEN_RETURN expression TOKEN_SC
    ;

print_stmt  : TOKEN_PRINT expression_list TOKEN_SC
    ;

param_list  : non_empty_param_list param
    | param
    |
    ;

non_empty_param_list : param TOKEN_COMMA
    ;

param       : ident TOKEN_COLON type
    ;

expression_list   : expression
    | 
    ;

optional_expression : expression
    |
    ;

expression  : TOKEN_IDENT
    ;

ident       : TOKEN_IDENT
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
}
