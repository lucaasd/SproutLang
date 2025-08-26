#include "../src/compiler/lexer/lexer.hpp"
#include "gtest/gtest.h"

TEST(LexerTests, TestKeywordOrIdentifier) {
  std::string input = std::string("function main\0");

  lexer::Lexer sproutLexer(&input);

  sproutLexer.tokenize();

  EXPECT_EQ(sproutLexer.tokens.size(), 2);
  EXPECT_EQ(sproutLexer.tokens[0].type, lexer::TokenType::FUNCTION);
  EXPECT_EQ(sproutLexer.tokens[1].type, lexer::TokenType::IDENTIFIER);
  EXPECT_EQ(sproutLexer.tokens[1].text, "main");
}
