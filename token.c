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
        case TOKEN_WS:
            return "whitespace";
        otherwise:
            return "other";
    }
}
