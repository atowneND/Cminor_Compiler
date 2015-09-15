#include "lex.yy.h"
#include "token.h"

/* function definitions */
const char *token_string(token_t t){
    switch(t){
        case TOKEN_ARRAY:
            return "ARRAY";
        case TOKEN_BOOL_T:
            return "BOOLEAN";
        case TOKEN_CHAR_T:
            return "CHARACTER";
        case TOKEN_ELSE:
            return "ELSE";
        case TOKEN_FALSE:
            return "FALSE";
        case TOKEN_FOR :
            return "FOR";
        case TOKEN_FCALL:
            return "FUNCTION_CALL";
        case TOKEN_IF:
            return "IF";
        case TOKEN_INT_T:
            return "INTEGER";
        case TOKEN_PRINT:
            return "PRINT";
        case TOKEN_RETURN:
            return "RETURN";
        case TOKEN_STR_T:
            return "STRING";
        case TOKEN_TRUE:
            return "TRUE";
        case TOKEN_VOID:
            return "VOID";
        case TOKEN_WHILE:
            return "WHILE";
        case TOKEN_IDENT:
            return "IDENTIFIER";
        case TOKEN_INTEGER:
            return "INTEGER_LITERAL";
        case TOKEN_CHAR:
            return "CHARACTER_LITERAL";
        case TOKEN_STRING:
            return "STRING_LITERAL";
        case TOKEN_LBRACK:
            return "LEFT_BRACKET";
        case TOKEN_RBRACK:
            return "RIGHT_BRACKET";
        case TOKEN_LBRACE:
            return "LEFT_BRACE";
        case TOKEN_RBRACE:
            return "RIGHT_BRACE";
        case TOKEN_LPAREN:
            return "LEFT_PARENTHESIS";
        case TOKEN_RPAREN:
            return "RIGHT_PARENTHESIS";
        case TOKEN_INC:
            return "POSTFIX_INCREMENT";
        case TOKEN_DEC:
            return "POSTFIX_DECREMENT";
        case TOKEN_NEG:
            return "MINUS";
        case TOKEN_POW:
            return "POWER";
        case TOKEN_MULT:
            return "MULTIPLICATION";
        case TOKEN_DIV:
            return "DIVISION";
        case TOKEN_MOD:
            return "MODULUS";
        case TOKEN_ADD:
            return "ADDITION";
        case TOKEN_LT:
            return "LT";
        case TOKEN_LE:
            return "LE";
        case TOKEN_GT:
            return "GT";
        case TOKEN_GE:
            return "GE";
        case TOKEN_EQ_COMP:
            return "EQUIVALENCE_COMPARISON";
        case TOKEN_NE_COMP:
            return "NONEQUIVALENCE_COMPARISON";
        case TOKEN_AND:
            return "AND";
        case TOKEN_OR:
            return "OR";
        case TOKEN_ASSIGN:
            return "ASSIGNMENT";
        case TOKEN_COM1:
            return "COMMENT_C++";
        case TOKEN_COM2:
            return "COMMENT_C";
        case TOKEN_COMMA:
            return "COMMA";
        case TOKEN_COLON:
            return "COLON";
        case TOKEN_SC:
            return "SEMICOLON";
        case TOKEN_WS:
            return "WHITESPACE";
        case TOKEN_OTHER:
            printf("TOKEN_OTHER: Cannot scan on token: %s\n",yytext);
            printf("\tPlease review input file. Exiting\n");
            exit(1);
        otherwise:
            printf("Cannot scan on token: %s\n",yytext);
            printf("Please review input file. Exiting\n");
            exit(1);
    }
}
