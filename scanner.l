%{
#include <stdio.h>
#include "token.h"
%}

NUMBER [0-9]*
STRING [a-zA-Z]*

%%
{NUMBER} {printf("TOKEN_NUMBER");}
{STRING} {printf("TOKEN_STRING");}

%%
