#ifndef TOKENS
#define TOKENS

#include <string>

namespace lexer {

    enum class TokenType {
        UNKNOWN = 0,
        IDENTIFIER = 1,
        CLASS = 2,
        STRUCT = 3,
        FUNCTION = 4,
        VAR = 5,
        IF = 6,
        ELSE = 7,
        FOR = 8,
        WHILE = 9,
        CHAR = 10,
        CHAR_LITERAL = 11,
        CHAR_ARRAY_LITERAL = 12,
        FLOAT_LITERAL = 13,
        FLOAT = 14,
        INT_LITERAL = 15,
        INT = 16,
        ARRAY = 17,
        POINTER = 18,
        ADD = 19,
        SUB = 20,
        MUL = 21,
        DIV = 22,
        MODULUS = 23,
        LT = 24,
        GT = 25,
        LEQ = 26,
        GEQ = 27,
        ASSIGN = 28,
        EQ = 29,
    };

    struct Token {
        std::string text;
        TokenType type;

        inline bool operator==(const Token& other) const {return text == other.text && type == other.type;}
    };

} // namespace lexer
#endif
