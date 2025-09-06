#include "../../src/compiler/lexer/lexer.hpp"
#include "../../src/compiler/lexer/tokens.hpp"
#include "gtest/gtest.h"
#include <iostream>

TEST(LexerTests, TestKeywordOrIdentifier) {
  std::string input = "function main";

  lexer::Lexer sproutLexer(&input);

  sproutLexer.tokenize();

  EXPECT_EQ(sproutLexer.tokens.size(), 2);
  EXPECT_EQ(sproutLexer.tokens[0].type, lexer::TokenType::FUNCTION);
  EXPECT_EQ(sproutLexer.tokens[1].type, lexer::TokenType::IDENTIFIER);
  EXPECT_EQ(sproutLexer.tokens[1].text, "main");
}

TEST(LexerTests, TestInteger) {
  std::string input = "123";

  lexer::Lexer sproutLexer(&input);

  sproutLexer.tokenize();

  EXPECT_EQ(sproutLexer.tokens.size(), 1);
  EXPECT_EQ(sproutLexer.tokens[0].text, "123");
  EXPECT_EQ(sproutLexer.tokens[0].type, lexer::TokenType::INT_LITERAL);
}

TEST(LexerTests, TestFloat) {
  std::string input = "3.14f";

  lexer::Lexer sproutLexer(&input);

  sproutLexer.tokenize();

  EXPECT_EQ(sproutLexer.tokens.size(), 1);
  EXPECT_EQ(sproutLexer.tokens[0].text, "3.14.f");
  EXPECT_EQ(sproutLexer.tokens[0].type, lexer::TokenType::FLOAT_LITERAL);
}

TEST(LexerTests, TestSpecial) { 
    std::string input = "= * == >= <=";

    std::vector expectedTokens = {
        lexer::Token{"=", lexer::TokenType::ASSIGN},
        lexer::Token{"*", lexer::TokenType::MUL},
        lexer::Token{"==", lexer::TokenType::EQ},
        lexer::Token{">=", lexer::TokenType::GEQ},
        lexer::Token{"<=", lexer::TokenType::LEQ}
    };

    lexer::Lexer sproutLexer(&input);

    sproutLexer.tokenize();

    for (const lexer::Token& item : sproutLexer.tokens)
    {
        std::cout << "Text: " << item.text << "Type: " << static_cast<int>(item.type) << "\n";
    }

    for (const lexer::Token& item : expectedTokens)
    {
        std::cout << "Expected Text: " << item.text << "Expected Type: " << static_cast<int>(item.type) << "\n";
    }

    
    EXPECT_EQ(sproutLexer.tokens.size(), 5);
    EXPECT_EQ(sproutLexer.tokens, expectedTokens);
}

TEST(LexerTests, TestCharEscape) {
    std::vector<std::string> inputs = {R"(\n)", R"(\0)", R"(\\)", R"(\')", R"(\")"};

    std::vector<char> output = {lexer::Lexer::findEscape(inputs[0]), lexer::Lexer::findEscape(inputs[1]), lexer::Lexer::findEscape(inputs[2]), lexer::Lexer::findEscape(inputs[3]), lexer::Lexer::findEscape(inputs[4])};

    std::vector<char> expected = {0x0A, 0x00, 0x5C, 0x27, 0x22};

    for (const char item : output) {
        std::cout << "Output: " << std::to_string(item);
    }

    for (const char item : expected) {
        std::cout << "Expected: " << std::to_string(item);
    }

    EXPECT_EQ(output, expected);
}


TEST(LexerTests, TestChar)
{
    std::string input = "'a' '\n'";
}
