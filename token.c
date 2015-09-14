#include "lex.yy.h"
#include "token.h"

/* function definitions */
const char *token_string(token_t t){
    switch(t){
        case 0:
            return "returned zero";
        case TOKEN_ARRAY:
            return "array";
        case TOKEN_BOOL_T:
            return "boolean type";
        case TOKEN_CHAR_T:
            return "character type";
        case TOKEN_ELSE:
            return "else";
        case TOKEN_FALSE:
            return "false";
        case TOKEN_FOR :
            return "for";
        case TOKEN_FCALL:
            return "function call";
        case TOKEN_IF:
            return "if";
        case TOKEN_INT_T:
            return "integer type";
        case TOKEN_PRINT:
            return "print";
        case TOKEN_RETURN:
            return "return";
        case TOKEN_STR_T:
            return "string type";
        case TOKEN_TRUE:
            return "true";
        case TOKEN_VOID:
            return "void";
        case TOKEN_WHILE:
            return "while";
        case TOKEN_IDENT:
            return "identifier";
        case TOKEN_INTEGER:
            return "integer";
        case TOKEN_CHAR:
            return "character";
        case TOKEN_STRING:
            return "string";
        case TOKEN_LBRACK:
            return "left bracket";
        case TOKEN_RBRACK:
            return "right bracket";
        case TOKEN_LBRACE:
            return "left brace";
        case TOKEN_RBRACE:
            return "right brace";
        case TOKEN_LPAREN:
            return "left parenthesis";
        case TOKEN_RPAREN:
            return "right parenthesis";
        case TOKEN_INC:
            return "postfix increment";
        case TOKEN_DEC:
            return "postfix decrement";
        case TOKEN_NEG:
            return "minus sign (subtraction or negation)";
        case TOKEN_POW:
            return "power";
        case TOKEN_MULT:
            return "multiplication";
        case TOKEN_DIV:
            return "division";
        case TOKEN_MOD:
            return "modulus";
        case TOKEN_ADD:
            return "addition";
        case TOKEN_LT:
            return "less than";
        case TOKEN_LE:
            return "less than or equal to";
        case TOKEN_GT:
            return "greater than";
        case TOKEN_GE:
            return "greater than or equal to";
        case TOKEN_EQ_COMP:
            return "equivalence comparison";
        case TOKEN_NE_COMP:
            return "nonequivalence comparison";
        case TOKEN_AND:
            return "logical and";
        case TOKEN_OR:
            return "logical or";
        case TOKEN_ASSIGN:
            return "assignment";
        case TOKEN_COM1:
            return "comment c++";
        case TOKEN_COM2:
            return "comment c";
        case TOKEN_COMMA:
            return "comma";
        case TOKEN_COLON:
            return "colon";
        case TOKEN_SC:
            return "semicolon";
        case TOKEN_WS:
            return "whitespace";
        case TOKEN_OTHER:
            printf("Cannot scan on token: %s\n",yytext);
            printf("Please review input file. Exiting\n");
            exit(1);
        otherwise:
            printf("Cannot scan on token: %s\n",yytext);
            printf("Please review input file. Exiting\n");
            exit(1);
    }
}
