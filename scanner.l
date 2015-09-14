%{
#include <stdio.h>
#include "token.h"
%}

/* */
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
IDENT   [a-zA-Z_][a-zA-Z_0-9]*
INTEGER  [+-]?[0-9]*
CHAR    '.'
STRING  \".*\"
WS      [ \t\n]

%%

{ARRAY}   {return TOKEN_ARRAY;}
{BOOL_T}  {return TOKEN_BOOL_T;}
{CHAR_T}  {return TOKEN_CHAR_T;}
{ELSE}    {return TOKEN_ELSE;}
{FALSE}   {return TOKEN_FALSE;}
{FOR}     {return TOKEN_FOR;}
{FCALL}   {return TOKEN_FCALL;}
{IF}      {return TOKEN_IF;}
{INT_T}   {return TOKEN_INT_T;}
{PRINT}   {return TOKEN_PRINT;}
{RETURN}  {return TOKEN_RETURN;}
{STR_T}   {return TOKEN_STR_T;}
{TRUE}    {return TOKEN_TRUE;}
{VOID}    {return TOKEN_VOID;}
{WHILE}   {return TOKEN_WHILE;}
{IDENT}   {return TOKEN_IDENT;}
{INTEGER} {return TOKEN_INTEGER;}
{CHAR}    {return TOKEN_CHAR;}
{STRING}  {return TOKEN_STRING;}
{WS}      {}

%%
