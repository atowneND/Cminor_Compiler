%{
#include <stdio.h>
#include "token.h"
%}

/* reserved words */
ARRAY   array
BOOL_T  boolean
CHAR_T  char
ELSE    else
FALSE   false
FOR     for
FCALL   function
IF      if
INT_T   int
PRINT   print
RETURN  return
STR_T   string
TRUE    true
VOID    void
WHILE   while

/* types */
IDENT   [a-zA-Z_][a-zA-Z_0-9]*
INTEGER [+-]?[0-9]+
CHAR    '.'|'\\.'
STRING  \".*\"

/* group */
LBRACK  \[
RBRACK  \]
LBRACE  \{
RBRACE  \}
LPAREN  \(
RPAREN  \)

/* operations */
INC     \+\+
DEC     \-\-
POW     \^
MULT    \*
DIV     \/
MOD     %
ADD     \+
NEG     -
LT      <
LE      <=
GT      >
GE      >=
EQ_COMP ==
NE_COMP !=
AND     &&
OR      \|\|
ASSIGN  =

/* comments */
CPP_COMMENT \/\/.*
%x C_COMMENT

/* delimiters */
COMMA   ,
COLON   :
SC      ;
WS      [ \t\n\r]*

%%

{ARRAY}             {return TOKEN_ARRAY;}
{BOOL_T}            {return TOKEN_BOOLEAN;}
{CHAR_T}            {return TOKEN_CHARACTER;}
{ELSE}              {return TOKEN_ELSE;}
{FALSE}             {return TOKEN_FALSE;}
{FOR}               {return TOKEN_FOR;}
{FCALL}             {return TOKEN_FCALL;}
{IF}                {return TOKEN_IF;}
{INT_T}             {return TOKEN_INTEGER;}
{PRINT}             {return TOKEN_PRINT;}
{RETURN}            {return TOKEN_RETURN;}
{STR_T}             {return TOKEN_STRING;}
{TRUE}              {return TOKEN_TRUE;}
{VOID}              {return TOKEN_VOID;}
{WHILE}             {return TOKEN_WHILE;}
{IDENT}             {return TOKEN_IDENT;}
{INTEGER}			{return TOKEN_INTEGER_LITERAL;}
{CHAR}              {return TOKEN_CHARACTER_LITERAL;}
{STRING}            {return TOKEN_STRING_LITERAL;}
{LBRACK}            {return TOKEN_LBRACK;}
{RBRACK}            {return TOKEN_RBRACK;}
{LBRACE}            {return TOKEN_LBRACE;}
{RBRACE}            {return TOKEN_RBRACE;}
{LPAREN}            {return TOKEN_LPAREN;}
{RPAREN}            {return TOKEN_RPAREN;}
{INC}	            {return TOKEN_INC;}
{DEC}	            {return TOKEN_DEC;}
{POW}	            {return TOKEN_POW;}
{MULT}	            {return TOKEN_MULT;}
{DIV}	            {return TOKEN_DIV;}
{MOD}	            {return TOKEN_MOD;}
{ADD}               {return TOKEN_ADD;}
{NEG}               {return TOKEN_NEG;}
{LT}	            {return TOKEN_LT;}
{LE}	            {return TOKEN_LE;}
{GT}	            {return TOKEN_GT;}
{GE}	            {return TOKEN_GE;}
{EQ_COMP}			{return TOKEN_EQ_COMP;}
{NE_COMP}			{return TOKEN_NE_COMP;}
{AND}	            {return TOKEN_AND;}
{OR}	            {return TOKEN_OR;}
{ASSIGN}            {return TOKEN_ASSIGN;}
{CPP_COMMENT}	    {return TOKEN_CPP_COMMENT;}
"/*"                {BEGIN(C_COMMENT);}
<C_COMMENT>"*/"     {BEGIN(INITIAL); return TOKEN_C_COMMENT;}
<C_COMMENT>.|\n     {}
{COMMA}	            {return TOKEN_COMMA;}
{COLON}	            {return TOKEN_COLON;}
{SC}	            {return TOKEN_SC;}
{WS}	            {}
.                   {return TOKEN_OTHER;}

%%
