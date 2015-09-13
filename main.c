#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "lex.yy.h"

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("enter one filename\n");
        exit(1);
    }
    char *filename = argv[1];
    printf("filename=%s\n",filename);
    return 0;
}
