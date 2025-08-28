#include "../src/compiler/lexer/lexer.hpp"
#include "compiler/lexer/tokens.hpp"
#include "gtest/gtest.h"

TEST(LexerTests, TestKeywordOrIdentifier) {
  std::string input = "function main\0";

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
