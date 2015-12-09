#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "type.h"
#include "stmt.h"
#include "decl.h"
#include "scope.h"
#include "expr.h"
#include "reg.h"

extern int yyparse();
extern struct expr * parser_result;
extern int yylex();
extern FILE * yyin;
extern char * yytext;
extern struct decl *ast_pointer;

extern const char *token_string(int t);
void name_resolution(void);
void generate_code(FILE *outputfile);

int fooctr = 0;

int indent = 0;
int error_counter = 0;
int scope_ctr = 0;
int global_ctr = 0;
int local_ctr = 0;
int param_ctr = 0;

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

    int action = 0;
    if (!strcmp(argv[1],"-scan")){
        action = 1;
        if (argc!=3){
            fprintf(stderr,"usage: ./cminor <option> <filename>\n");
            exit(1);
        }
    }else if (!strcmp(argv[1],"-print")){
        action = 2;
        if (argc!=3){
            fprintf(stderr,"usage: ./cminor <option> <filename>\n");
            exit(1);
        }
    }else if (!strcmp(argv[1],"-resolve")){
        action = 3;
        if (argc!=3){
            fprintf(stderr,"usage: ./cminor <option> <filename>\n");
            exit(1);
        }
    }else if (!strcmp(argv[1],"-typecheck")){ action = 4;
        if (argc!=3){
            fprintf(stderr,"usage: ./cminor <option> <filename>\n");
            exit(1);
        }
    }else if (!strcmp(argv[1],"-codegen")){
        action = 5;
        if (argc!=4){
            fprintf(stderr,"usage: ./cminor <option> <sourcefilename> <outputfilename>\n");
            exit(1);
        }
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
            name_resolution();
            break;
        case 4:
            printf("typechecking\n");
            name_resolution();
            break;
        case 5:
            printf("code generation\n");
            name_resolution();
            if (error_counter == 0){
                printf("scanning, parsing, name resolution, and typechecking successful\n");
            }
            char *outputfile = argv[3];
            FILE *fd = fopen(outputfile,"w");
            generate_code(fd);
            break;
        default:
            fprintf(stderr,"Incorrect option selected\n");
            break;
    }
	fclose(yyin);
    
    return 0;
}

void name_resolution(void){
    scope_enter();
    if (yyparse()!=0){
        fprintf(stderr,"Error parsing\n");
    } else {
        printf("parse successful\n");
    }

    decl_resolve(ast_pointer);
    if (error_counter == 0) { 
        decl_typecheck(ast_pointer);
    }else{
        fprintf(stderr,"Please resolve all naming errors before moving on to typechecking\n");
    }
    scope_exit();

    if (error_counter == 1){ 
        fprintf(stderr,"%i name resolution error\n",error_counter);
    } else if (error_counter > 0) {
        fprintf(stderr,"%i name resolution errors\n",error_counter);
    } else if (error_counter == 0) {
        printf("%i name resolution errors\n",error_counter);
    }
}

void generate_code(FILE *fd){
    init_registers();
    decl_codegen(ast_pointer, fd);
}
