%{
#include "token.h"
%}

NUMBER = [0-9]
LETTER = [a-zA-Z]

%%
NUMBER {return TOKEN_NUMBER;}
LETTER {return TOKEN_LETTER;}

%%
