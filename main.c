#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lex.yy.h"

int main(int argc, char *argv[]){
//    if(argc!=2){
//        printf("enter one filename\n");
//        exit(1);
//    }
//    char *filename = argv[1];

    // TEST CASE
    char *filename = "testfoo";
    FILE *yyin = fopen(filename,"r");
    int retval = yylex();
    // yyin - file with symbols to be read
    // yylex - scans input, runs machinery, returns one integer for one token type
    // yytext - global array to look at token
    
    printf("filename=%s\n",filename);
    return 0;
}
