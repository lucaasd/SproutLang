#ifndef LEXER
#define LEXER

#include "tokens.hpp"
#include <map>
#include <string>
#include <vector>

namespace lexer {

extern const std::map<std::string, TokenType> keywords;
extern const std::map<std::string, TokenType> singleCharTokens;
extern const std::map<std::string, TokenType> lookaheadTokens;
extern const std::map<std::string, TokenType> commentsCharTokens;

class Lexer {
public:
  Lexer(std::string *_input) : input(_input), index(0) {}
  ~Lexer();
  std::vector<Token> tokens;
  std::string *input;
  void tokenize();
  char CurrentChar();
  void advance();
  void keywordOrIdentifier();
  size_t index;
};

#endif
}
