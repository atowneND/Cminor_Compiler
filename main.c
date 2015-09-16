#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lex.yy.h"

int main(int argc, char *argv[]){
    // parse input
    if (argc==1){
        fprintf(stderr,"usage: ./cminor -scan <filename>\nPlease enter an option and its arguments\n");
        exit(1);
    }
    else if (argc==2){
        fprintf(stderr,"usage: ./cminor -scan <filename>\nPlease enter a filename\n");
        exit(1);
    }
    else if (argc!=3){
        fprintf(stderr,"usage: ./cminor -scan <filename>\n");
        exit(1);
    }
    if (!strcmp(argv[2],"-scan")){
        fprintf(stderr,"usage: ./cminor -scan <filename>\nno flags other than -scan allowed at this time\n");
        exit(1);
    }
    char *filename = argv[2];
    yyin = fopen(filename,"r");
    if (yyin==NULL){
        fprintf(stderr,"Could not open file\n");
        exit(1);
    }

    // Scan
    int returned_token;
    while(1){
        returned_token = yylex();
	    if(!returned_token){
	        break;
        }
        else{
            printf("%s\n",token_string(returned_token));
        }
    }
	fclose(yyin);
    
    return 0;
}
