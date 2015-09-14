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
    int retval;
    while(1){
	    retval=yylex();
	    if(!retval){
	        printf("EOF\n");
	        break;
        }
        else{
            printf("yy: %s\n",token_string(retval));
        }
    }
	    fclose(yyin);
    
    return 0;
}
