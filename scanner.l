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
NUMBER  [0-9]*
CHAR    '.'
STRING  \".*\"
WORD    [a-zA-Z]*

%%

{ARRAY}   {printf("TOKEN_ARRAY_T");}
{BOOL_T}  {printf("TOKEN_BOOL_T");}
{CHAR_T}  {printf("TOKEN_CHAR_T");}
{ELSE}    {printf("TOKEN_ELSE");}
{FALSE}   {printf("TOKEN_FALSE");}
{FOR}     {printf("TOKEN_FOR");}
{FCALL}   {printf("TOKEN_FUNCTION");}
{IF}      {printf("TOKEN_IF");}
{INT_T}   {printf("TOKEN_INT_T");}
{PRINT}   {printf("TOKEN_PRINT");}
{RETURN}  {printf("TOKEN_RETURN");}
{STR_T}   {printf("TOKEN_STRING_T");}
{TRUE}    {printf("TOKEN_TRUE");}
{VOID}    {printf("TOKEN_VOID");}
{WHILE}   {printf("TOKEN_WHILE");}
{IDENT}   {printf("TOKEN_IDENT");}
{NUMBER}  {printf("TOKEN_NUMBER");}
{CHAR}    {printf("TOKEN_CHAR");}
{STRING}  {printf("TOKEN_STRING");}
{WORD}    {printf("word");}

%%
