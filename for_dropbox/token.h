/* enumerate tokens */
//enum token{
//    TOKEN_ARRAY=1,
//    TOKEN_BOOLEAN,
//    TOKEN_CHARACTER,
//    TOKEN_ELSE,
//    TOKEN_FALSE,
//    TOKEN_FOR ,
//    TOKEN_FCALL,
//    TOKEN_IF,
//    TOKEN_INTEGER,
//    TOKEN_PRINT,
//    TOKEN_RETURN,
//    TOKEN_STRING,
//    TOKEN_TRUE,
//    TOKEN_VOID,
//    TOKEN_WHILE,
//    TOKEN_IDENT,
//    TOKEN_INTEGER_LITERAL,
//    TOKEN_CHARACTER_LITERAL,
//    TOKEN_STRING_LITERAL,
//    TOKEN_LBRACK,
//    TOKEN_RBRACK,
//    TOKEN_LBRACE,
//    TOKEN_RBRACE,
//    TOKEN_LPAREN,
//    TOKEN_RPAREN,
//    TOKEN_INC,
//    TOKEN_DEC,
//    TOKEN_NEG,
//    TOKEN_POW,
//    TOKEN_MULT,
//    TOKEN_DIV,
//    TOKEN_MOD,
//    TOKEN_ADD,
//    TOKEN_LT,
//    TOKEN_LE,
//    TOKEN_GT,
//    TOKEN_GE,
//    TOKEN_EQ_COMP,
//    TOKEN_NE_COMP,
//    TOKEN_AND,
//    TOKEN_OR,
//    TOKEN_NOT,
//    TOKEN_ASSIGN,
//    TOKEN_CPP_COMMENT,
//    TOKEN_C_COMMENT,
//    TOKEN_COMMA,
//    TOKEN_COLON,
//    TOKEN_SC,
//    TOKEN_WS,
//    TOKEN_OTHER,
//    TOKEN_EOF,
//};
//typedef enum token token_t;

/* function declarations */
const char *token_string(int t);
char *scan_text(void);
void error_end(int error_type);
