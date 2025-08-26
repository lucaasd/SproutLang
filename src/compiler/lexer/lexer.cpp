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
            }
            advance();
        }
    }

    char Lexer::CurrentChar() { return index < input->size() ? (*input)[index] : '\0'; }

    void Lexer::advance() {
        if (index < input->size())
        {
            index++;
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
