#include "lex.yy.h"
#include "token.h"
#include <string.h>

/* function definitions */
const char *token_string(token_t t){
    int output_length = (int)strlen(yytext);
    char *output_string = malloc(sizeof(char)*output_length);
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
            sprintf(output_string,"IDENTIFIER");
            break;
        case TOKEN_INTEGER_LITERAL:
            sprintf(output_string,"INTEGER_LITERAL");
            break;
        case TOKEN_CHARACTER_LITERAL:
            sprintf(output_string,"CHARACTER_LITERAL %s",yytext);
            break;
        case TOKEN_STRING_LITERAL:
            sprintf(output_string,"STRING_LITERAL %s",yytext);
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
        case TOKEN_ASSIGN:
            sprintf(output_string,"ASSIGNMENT");
            break;
        case TOKEN_COM1:
            sprintf(output_string,"COMMENT_C++");
            break;
        case TOKEN_COM2:
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
            fprintf(stderr,"scan error: %s is not a valid character\n",yytext);
            exit(1);
        otherwise:
            fprintf(stderr,"scan error: %s is not a valid character\n",yytext);
            exit(1);
    }
    return output_string;
}

void strip_first_and_last(void){
    int len = (int)strlen(yytext);
    sprintf(yytext,"%.*s",len-2,&(yytext[1]));
}
