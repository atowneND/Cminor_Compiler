/* enumerate tokens */
enum token{
    TOKEN_ARRAY=1,
    TOKEN_BOOL_T,
    TOKEN_CHAR_T,
    TOKEN_ELSE,
    TOKEN_FALSE,
    TOKEN_FOR ,
    TOKEN_FCALL,
    TOKEN_IF,
    TOKEN_INT_T,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_STR_T,
    TOKEN_TRUE,
    TOKEN_VOID,
    TOKEN_WHILE,
    TOKEN_IDENT,
    TOKEN_INTEGER,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_WS,
};
typedef enum token token_t;

/* function declarations */
const char *token_string(token_t t);
