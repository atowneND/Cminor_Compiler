/* enumerate tokens */
enum token{
    TOKEN_NUMBER,
    TOKEN_LETTER
};

/* define token type */
typedef enum token token_t;

/* function prototypes */
const char * token_string(token_t t);
