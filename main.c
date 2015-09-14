#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lex.yy.h"

int main(int argc, char *argv[]){
    // parse input

    // TEST CASE
    // put it into a function
    char *filename = "scannerTests/test1";
    yyin = fopen(filename,"r");
    yylex();
    
    return 0;
}
