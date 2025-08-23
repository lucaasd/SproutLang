#ifndef TOKENS
#define TOKENS

#include <string>

enum class TokenType {
    IDENTIFIER,
    CLASS,
    STRUCT,
    FUNCTION,
    VAR,
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
};

struct Token {
    std::string text;
    TokenType value;
};

#endif
