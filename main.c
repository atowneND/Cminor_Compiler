#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "decl.h"
#include "expr.h"
#include "stmt.h"
#include "symbol.h"
#include "type.h"

extern int yyparse();
extern struct expr * parser_result;
extern int yylex();
extern FILE * yyin;
extern char * yytext;
extern struct decl *ast_pointer;

extern const char *token_string(int t);

int indent = 0;
int error_counter = 0;
int scope_ctr = 0;

int main(int argc, char *argv[]){
    // check input
    if (argc==1){
        fprintf(stderr,"usage: ./cminor <option> <filename>\nPlease enter an option and its arguments\n");
        exit(1);
    }
    else if (argc==2){
        fprintf(stderr,"usage: ./cminor <option> <filename>\nPlease enter a filename\n");
        exit(1);
    }
    else if (argc!=3){
        fprintf(stderr,"usage: ./cminor <option> <filename>\n");
        exit(1);
    }

    int action = 0;
    if (!strcmp(argv[1],"-scan")){
        action = 1;
    }else if (!strcmp(argv[1],"-print")){
        action = 2;
    }else if (!strcmp(argv[1],"-resolve")){
        action = 3;
    }else if (!strcmp(argv[1],"-typecheck")){
        action = 4;
    }else{
        fprintf(stderr,"usage: ./cminor <option> <filename>\n<option> must be -scan or -resolve or -typecheck\n");
        exit(1);
    }

    // open file
    char *filename = argv[2];
    yyin = fopen(filename,"r");
    if (yyin==NULL){
        fprintf(stderr,"Could not open file\n");
        exit(1);
    }

    // scan, parse, etc.
    int returned_token;
    switch (action){
        case 1:
            // Scan
            while(1){
                returned_token = yylex();
                printf("%s\n",token_string(returned_token));
//                printf("%i\n",returned_token);
                if(!returned_token){
                    break;
                }
            }
            break;
        case 2:
            // parse
            if (yyparse()==0){
                printf("parse successful\n");
                decl_print(ast_pointer);
            }
            break;
        case 3:
            if (yyparse()!=0){
                fprintf(stderr,"Error parsing\n");
            } else {
                printf("parse successful\n");
            }
            break;
        case 4:
            printf("typechecking\n");
            break;
        default:
            fprintf(stderr,"Incorrect option selected\n");
            break;
    }
	fclose(yyin);
    
    return 0;
}
