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
