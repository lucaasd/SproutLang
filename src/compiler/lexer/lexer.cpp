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

    const std::map<std::string, TokenType> singleCharTokens = {
        {"+", TokenType::ADD},
        {"-", TokenType::SUB},
        {"*", TokenType::MUL},
        {"/", TokenType::DIV},
        {"%", TokenType::MODULUS},
        {"<", TokenType::LT},
        {"=", TokenType::ASSIGN},
        {">", TokenType::GT},
    };

    const std::map<std::string, TokenType> lookaheadTokens {
        {"<=", TokenType::LEQ},
        {">=", TokenType::GEQ},
        {"==", TokenType::EQ}

    };

    const std::map<std::string, TokenType> commentsCharTokens;

    Lexer::~Lexer() {}

    void Lexer::tokenize()
    {
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
                special();
            }
        }
    }

    char Lexer::CurrentChar() { return index < input->size() ? (*input)[index] : '\0'; }

    void Lexer::advance()
    {
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

    void Lexer::keywordOrIdentifier()
    {
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

    void Lexer::special()
    {
        int start = index;

        auto it = singleCharTokens.find(std::string(1, CurrentChar()));
        advance();

        if (it != singleCharTokens.end())
        {

            std::string key = input->substr(start, 2);

            auto it2 = lookaheadTokens.find(key);

            it2 != lookaheadTokens.end() ? tokens.push_back(Token{it2->first, it2->second}) : tokens.push_back(Token{it->first, it->second});
        } else {
            tokens.push_back(Token{"unknown", TokenType::UNKNOWN});
        }
        advance();
    }

void Lexer::character()
    {
        if (CurrentChar() != '\'')
        {
            return;
        }

        advance();

        std::vector<char> charContent;

        while (CurrentChar() != '\'')
        {
            if (CurrentChar() == '\\') {
                charContent.push_back(findEscape(std::string(1, CurrentChar())));
            }

            charContent.push_back(CurrentChar());
        }

        if (charContent.size() > 4)
        {
            tokens.push_back(Token{"unknown", TokenType::UNKNOWN});
        }

        tokens.push_back(Token{std::string(charContent.begin(), charContent.end()), TokenType::CHAR_LITERAL});
    }

    char Lexer::findEscape(std::string escape) {
       int index = 1;

       switch (escape[index]) {
           case 'n': return 0x0A;
           case '0': return 0x00;
           case '\\': return 0x5C;
           case '\'': return 0x27;
           case '\"': return 0x22;
           default: return 0xFF; // Unkown

       }
    }
} // namespace lexer
