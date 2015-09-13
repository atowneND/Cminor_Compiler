#include "token.h"
const char *token_string(token_t t){
    switch(t){
        case TOKEN_NUMBER:
            return "number";
            break;
        case TOKEN_LETTER:
            return "letter";
            break;
    }
}
