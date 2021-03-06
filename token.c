//#include "lex.yy.h"
#include "parser.tab.h"
#include "token.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern char * yytext;

/* function definitions */
const char *token_string(int t){
    int output_length = (int)strlen(yytext);
    char *output_string = malloc(sizeof(char)*output_length);
    char *text_string = malloc(sizeof(char)*output_length);
    memset(output_string,0,output_length);
    memset(text_string,0,output_length);
    switch(t){
        case TOKEN_ARRAY:
            sprintf(output_string,"ARRAY");
            break;
        case TOKEN_BOOLEAN:
            sprintf(output_string,"BOOLEAN");
            break;
        case TOKEN_CHARACTER:
            sprintf(output_string,"CHARACTER");
            break;
        case TOKEN_ELSE:
            sprintf(output_string,"ELSE");
            break;
        case TOKEN_FALSE:
            sprintf(output_string,"FALSE");
            break;
        case TOKEN_FOR :
            sprintf(output_string,"FOR");
            break;
        case TOKEN_FCALL:
            sprintf(output_string,"FUNCTION");
            break;
        case TOKEN_IF:
            sprintf(output_string,"IF");
            break;
        case TOKEN_INTEGER:
            sprintf(output_string,"INTEGER");
            break;
        case TOKEN_PRINT:
            sprintf(output_string,"PRINT");
            break;
        case TOKEN_RETURN:
            sprintf(output_string,"RETURN");
            break;
        case TOKEN_STRING:
            sprintf(output_string,"STRING");
            break;
        case TOKEN_TRUE:
            sprintf(output_string,"TRUE");
            break;
        case TOKEN_VOID:
            sprintf(output_string,"VOID");
            break;
        case TOKEN_WHILE:
            sprintf(output_string,"WHILE");
            break;
        case TOKEN_IDENT:
            if (output_length>256){
                error_end(1);
            }
            sprintf(output_string,"IDENTIFIER");
            break;
        case TOKEN_INTEGER_LITERAL:
            sprintf(output_string,"INTEGER_LITERAL");
            break;
        case TOKEN_CHARACTER_LITERAL:
            text_string = scan_text();
            sprintf(output_string,"CHARACTER_LITERAL %s",text_string);
            break;
        case TOKEN_STRING_LITERAL:
            text_string = scan_text();
            sprintf(output_string,"STRING_LITERAL %s",text_string);
            break;
        case TOKEN_LBRACK:
            sprintf(output_string,"LEFT_BRACKET");
            break;
        case TOKEN_RBRACK:
            sprintf(output_string,"RIGHT_BRACKET");
            break;
        case TOKEN_LBRACE:
            sprintf(output_string,"LEFT_BRACE");
            break;
        case TOKEN_RBRACE:
            sprintf(output_string,"RIGHT_BRACE");
            break;
        case TOKEN_LPAREN:
            sprintf(output_string,"LEFT_PARENTHESIS");
            break;
        case TOKEN_RPAREN:
            sprintf(output_string,"RIGHT_PARENTHESIS");
            break;
        case TOKEN_INC:
            sprintf(output_string,"POSTFIX_INCREMENT");
            break;
        case TOKEN_DEC:
            sprintf(output_string,"POSTFIX_DECREMENT");
            break;
        case TOKEN_NEG:
            sprintf(output_string,"MINUS");
            break;
        case TOKEN_POW:
            sprintf(output_string,"POWER");
            break;
        case TOKEN_MULT:
            sprintf(output_string,"MULTIPLICATION");
            break;
        case TOKEN_DIV:
            sprintf(output_string,"DIVISION");
            break;
        case TOKEN_MOD:
            sprintf(output_string,"MODULUS");
            break;
        case TOKEN_ADD:
            sprintf(output_string,"ADDITION");
            break;
        case TOKEN_LT:
            sprintf(output_string,"LT");
            break;
        case TOKEN_LE:
            sprintf(output_string,"LE");
            break;
        case TOKEN_GT:
            sprintf(output_string,"GT");
            break;
        case TOKEN_GE:
            sprintf(output_string,"GE");
            break;
        case TOKEN_EQ_COMP:
            sprintf(output_string,"EQUIVALENCE_COMPARISON");
            break;
        case TOKEN_NE_COMP:
            sprintf(output_string,"NONEQUIVALENCE_COMPARISON");
            break;
        case TOKEN_AND:
            sprintf(output_string,"AND");
            break;
        case TOKEN_OR:
            sprintf(output_string,"OR");
            break;
        case TOKEN_NOT:
            sprintf(output_string,"NOT");
            break;
        case TOKEN_ASSIGN:
            sprintf(output_string,"ASSIGNMENT");
            break;
        case TOKEN_CPP_COMMENT:
            sprintf(output_string,"COMMENT_CPP");
            break;
        case TOKEN_C_COMMENT:
            sprintf(output_string,"COMMENT_C");
            break;
        case TOKEN_COMMA:
            sprintf(output_string,"COMMA");
            break;
        case TOKEN_COLON:
            sprintf(output_string,"COLON");
            break;
        case TOKEN_SC:
            sprintf(output_string,"SEMICOLON");
            break;
        case TOKEN_WS:
            sprintf(output_string,"WHITESPACE");
            break;
        case TOKEN_OTHER:
            error_end(0);
            break;
        case TOKEN_EOF:
            error_end(2);
            break;
//        otherwise:
//            error_end(0);
//            break;
    }
    return output_string;
}

char *scan_text(void){
    int len = (int)strlen(yytext);
    char *newstring = malloc(sizeof(char)*len);
    memset(newstring,0,len);
    int i,esc;
    esc = 0;
    char my_yy_c;

    if (yytext[0]=='\''){
        if ((len!=4) && (yytext[1]=='\\')){
            error_end(3);
        }
        else if ((len!=3) && (yytext[1]!='\\')) {
            error_end(3);
        }
    }

    for (i=1; i<len-1; i++){
        if (yytext[i]=='\\'){
            switch (yytext[i+1]){
                case 'n':
                    my_yy_c = '\n';
                    break;
                case 'r':
                    my_yy_c = '\r';
                    break;
                case 't':
                    my_yy_c = '\t';
                    break;
                case '0':
                    my_yy_c = '\0';
                    break;
//                otherwise:
//                  my_yy_c = yytext[i+1];
//                  break;
            }
            newstring[i-1] = my_yy_c;
            esc = 1;
        }
        else if (!esc){
            newstring[i-1] = yytext[i];
            esc = 0;
        }
        if (((int)yytext[i]<0) || ((int)yytext[i]>177)){
            error_end(4);
        }
    }

    len = (int)strlen(newstring);
    if (len>256){
        error_end(1);
    }
    return newstring;
}

void error_end(int error_type){
    switch (error_type){
        case 0:
            fprintf(stderr,"scan error: %s is not a valid character\n",yytext);
            break;
        case 1:
            fprintf(stderr,"scan error: token is longer than 256 characters\n");
            break;
        case 2:
            fprintf(stderr,"scan error: end of file reached before token could be matched\n");
            break;
        case 3:
            fprintf(stderr,"scan error: characters literals must contain only one character\n");
            break;
        case 4:
            fprintf(stderr,"scan error: %s contains invalid ascii character(s)\n",yytext);
            break;
    }
            exit(1);
}
