#include "lexer.hpp"
#include "tokens.hpp"
#include <cctype>
#include <string>

namespace lexer {
// clang-format off
    const std::map<std::string, TokenType> keywords = {
        {"class", TokenType::CLASS},
        {"struct", TokenType::STRUCT},
        {"function", TokenType::FUNCTION},
        {"var", TokenType::VAR},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"for", TokenType::FOR},
        {"while", TokenType::WHILE}
    };
    const std::map<std::string, TokenType> singleCharTokens;
    const std::map<std::string, TokenType> lookaheadTokens;
    const std::map<std::string, TokenType> commentsCharTokens;

    Lexer::~Lexer() {}

    void Lexer::tokenize() {
        while (CurrentChar() != '\0') {
            if (std::isspace(CurrentChar())) {
                while (std::isspace(CurrentChar())) {
                    advance();
                }
            } else if (std::isalpha(CurrentChar())) {
                keywordOrIdentifier();
            } else if (std::isdigit(CurrentChar()))
            {
                digit();
            } else {

            }
        }
    }

    char Lexer::CurrentChar() { return index < input->size() ? (*input)[index] : '\0'; }

    void Lexer::advance() {
        if (index < input->size())
        {
            index++;
        }
    }

    void Lexer::digit()
    {
        int start = index;
        while (std::isdigit(CurrentChar()))
        {
            advance();
        }

        int len = index - start;

        std::string integerPart = input->substr(start, len);

        if (CurrentChar() == '.')
        {
            advance();
            int start = index;
            while (std::isdigit(CurrentChar()))
            {
                advance();
            }

            int len = index - start;

            std::string decimalPart = input->substr(start, len);

            {
                int start = index;

                while (std::isalpha(CurrentChar()))
                {
                    advance();
                }

                int len = index - start;

                std::string suffix = input->substr(start, len);



                tokens.push_back(Token{integerPart + "." + decimalPart + "." + suffix, TokenType::FLOAT_LITERAL});
            }
        } else {
            tokens.push_back(Token{integerPart, TokenType::INT_LITERAL});
        }
    }

    void Lexer::keywordOrIdentifier() {
        int start = index;
        while (std::isalpha(CurrentChar())) {
            advance();
        }
        int len = index - start;
        std::string text = input->substr(start, len);
        TokenType type = TokenType::IDENTIFIER;

        auto it = keywords.find(text);

        if (it != keywords.end()) {
            type = it->second;
            tokens.push_back(Token{text, type});
        } else {
            tokens.push_back(Token{text, TokenType::IDENTIFIER});
        }
    }
} // namespace lexer
