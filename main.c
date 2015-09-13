#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lex.yy.h"

int main(int argc, char *argv[]){
    // parse input

    // TEST CASE
    // put it into a function
    char *filename = "test_deleteme";
    yyin = fopen(filename,"r");
    yylex();
    
    return 0;
}
