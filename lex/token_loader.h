// MIT License

// Copyright (c) 2020 Edward Liu

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LEX_TOKEN_LOADER_H_
#define LEX_TOKEN_LOADER_H_

#include <iostream>
#include <string>
#include <vector>

#include "lex/types.h"

namespace elsh {
namespace lex {

class TokenLoader {
 public:
  explicit TokenLoader(std::basic_istream<char>* const stream);

  /// @brief Get next token.
  Token GetToken();
  /// @brief Get all available tokens. End with `EOI` or unknown token.
  std::vector<Token> GetAllTokens();

 private:
  void GetNextChar();
  /// @brief Current we have the charater "/" and need to decide whether it's a
  /// division operator or a start of comments.
  Token DivisionOrComment(const int line, const int col);
  Token CharSplit(const int line, const int col);
  Token StringSplit(const int line, const int col);
  Token IndentifierOrValue(const int line, const int col);
  TokenType GetIdentifierType(const std::string& text);
  Token Follow(const char next, const TokenType is_yes_token,
               const TokenType is_no_token, const int line, const int col);

 private:
  std::basic_istream<char>* const stream_;
  char current_char_ = ' ';
  char last_char_;

  int current_line_ = 1;
  int current_col_ = 0;
};

}  // namespace lex
}  // namespace elsh

#endif  // LEX_TOKEN_LOADER_H_
