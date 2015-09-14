#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lex.yy.h"

int main(int argc, char *argv[]){
    // parse input
//    if (argc==1){
//        printf("usage: ./cminor -scan <filename>\nPlease enter an option and its arguments\n");
//        exit(1);
//    }
//    else if (argc==2){
//        printf("usage: ./cminor -scan <filename>\nPlease enter a filename\n");
//        exit(1);
//    }
//    else if (argc!=3){
//        printf("usage: ./cminor -scan <filename>\n");
//        exit(1);
//    }
//    if (strcmp(argv[2],"-scan")){
//        char *filename=argv[2];
//        printf("filename=%s\n",filename);
//    }
//    exit(1);

    // Scan
    char *filename = "scannerTests/test1";
    yyin = fopen(filename,"r");
    int retval;
    while(1){
        retval = yylex();
        if(!retval){
            printf("End of file\n");
            break;
        }
        printf("%s\n",token_string(retval));
    }
    
    return 0;
}
