// Copyright

#ifndef LEX_TOKEN_LOADER_H_
#define LEX_TOKEN_LOADER_H_

#include <fstream>
#include <string>

#include "lex/types.h"

namespace lex {

class TokenLoader {
 public:
  explicit TokenLoader(const std::string& source_filename)
      : source_fs_(source_filename) {}

  Token GetToken();

 private:
  void GetNextChar();

  Token DivisionOrComment(const int line, const int col);
  Token CharSplit(const int line, const int col);
  Token StringSplit(const int line, const int col);
  Token IndentifierOrInteger(const int line, const int col);
  TokenType GetIdentifierType(const std::string& text);
  Token Follow(const char next, const TokenType is_yes_token,
               const TokenType is_no_token, const int line, const int col);

  void Error(const std::string& error_msg);

 private:
  std::ifstream source_fs_;
  char current_char_ = ' ';
  char last_char_;

  int current_line_ = 1;
  int current_col_ = 0;
};

}  // namespace lex

#endif  // LEX_TOKEN_LOADER_H_
