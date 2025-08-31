#ifndef TOKENS
#define TOKENS

#include <string>

namespace lexer {

    enum class TokenType {
        UNKNOWN,
        IDENTIFIER,
        CLASS,
        STRUCT,
        FUNCTION,
        VAR,
        IF,
        ELSE,
        FOR,
        WHILE,
        CHAR,
        CHAR_LITERAL,
        CHAR_ARRAY_LITERAL,
        FLOAT_LITERAL,
        FLOAT,
        INT_LITERAL,
        INT,
        ARRAY,
        POINTER,
        ADD,
        SUB,
        MUL,
        DIV,
        MODULUS,
        LT,
        GT,
        LEQ,
        GEQ,
<<<<<<< HEAD
        ASSIGN,
        EQ
=======
>>>>>>> 47a3363264cb32ac2dc79d5acd775f58d3e5c426
    };

    struct Token {
        std::string text;
        TokenType type;
    };

} // namespace lexer
#endif
