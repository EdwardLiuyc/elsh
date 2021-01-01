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

#include "lex/token_loader.h"

#include <iostream>
#include <unordered_map>

namespace elsh {
namespace lex {
namespace {
const std::unordered_map<char, TokenType> kSimpleTokenMap{
    {'{', TokenType::kTokenSymLbrace},    {'}', TokenType::kTokenSymRbrace},
    {'(', TokenType::kTokenSymLparen},    {')', TokenType::kTokenSymRparen},
    {'+', TokenType::kTokenOpAdd},        {'-', TokenType::kTokenOpSub},
    {'*', TokenType::kTokenOpMul},        {'%', TokenType::kTokenOpMod},
    {';', TokenType::kTokenSymSemiColon}, {',', TokenType::kTokenSymComma}};
}

Token TokenLoader::GetToken() {
  while (isspace(current_char_)) {
    GetNextChar();
  }

  const int start_line = current_line_;
  const int start_col = current_col_;
  if (kSimpleTokenMap.count(current_char_) > 0) {
    GetNextChar();
    return Token{kSimpleTokenMap.at(last_char_), start_line, start_col, {0}};
  } else {
    switch (current_char_) {
      case '/':
        GetNextChar();
        return DivisionOrComment(start_line, start_col);
      case '\'':
        GetNextChar();
        return CharSplit(start_line, start_col);
      case '<':
        GetNextChar();
        return Follow('=', TokenType::kTokenOpLeq, TokenType::kTokenOpLss,
                      start_line, start_col);
      case '>':
        GetNextChar();
        return Follow('=', TokenType::kTokenOpGeq, TokenType::kTokenOpGtr,
                      start_line, start_col);
      case '=':
        GetNextChar();
        return Follow('=', TokenType::kTokenOpEq, TokenType::kTokenOpAssign,
                      start_line, start_col);
      case '!':
        GetNextChar();
        return Follow('=', TokenType::kTokenOpNeq, TokenType::kTokenOpNot,
                      start_line, start_col);
      case '&':
        GetNextChar();
        return Follow('&', TokenType::kTokenOpAnd, TokenType::kTokenEOI,
                      start_line, start_col);
      case '|':
        GetNextChar();
        return Follow('|', TokenType::kTokenOpOr, TokenType::kTokenEOI,
                      start_line, start_col);
      case '"':
        return StringSplit(start_line, start_col);
      case EOF:
        return Token{TokenType::kTokenEOI, start_line, start_col, {0}};
      default:
        return IndentifierOrValue(start_line, start_col);
    }
  }
}

std::vector<Token> TokenLoader::GetAllTokens() {
  std::vector<Token> all_tokens;
  do {
    all_tokens.push_back(GetToken());

    if (all_tokens.back().tok_type == TokenType::kTokenUnknown) {
      break;
    }
  } while (all_tokens.back().tok_type != TokenType::kTokenEOI);

  return all_tokens;
}

void TokenLoader::GetNextChar() {
  last_char_ = current_char_;
  if (stream_->get(current_char_)) {
    ++current_col_;
    if (current_char_ == '\n') {
      ++current_line_;
      current_col_ = 0;
    }
  } else {
    current_char_ = EOF;
  }
}

Token TokenLoader::DivisionOrComment(const int line, const int col) {
  if (current_char_ != '*') {
    return Token{TokenType::kTokenOpDiv, line, col, {0}};
  }

  /* comment found */
  GetNextChar();
  for (;;) {
    if (current_char_ == '*') {
      GetNextChar();
      if (current_char_ == '/') {
        GetNextChar();
        // We heve skiped all comments.
        return GetToken();
      }
    } else if (current_char_ == EOF) {
      return Token(TokenType::kTokenUnknown, line, col, "EOF in comment");
    } else {
      GetNextChar();
    }
  }
}

Token TokenLoader::CharSplit(const int line, const int col) {
  if (current_char_ == '\'') {
    return Token(TokenType::kTokenUnknown, line, col,
                 "empty character constant");
  }

  char n = current_char_;
  if (current_char_ == '\\') {
    GetNextChar();
    if (current_char_ == 'n') {
      n = '\n';
    } else if (current_char_ == '\\') {
      n = '\\';
    } else {
      return Token(TokenType::kTokenUnknown, line, col,
                   "gettok: unknown escape sequence \\" + current_char_);
    }
  }

  GetNextChar();
  if (current_char_ != '\'') {
    return Token(TokenType::kTokenUnknown, line, col,
                 "multi-character constant");
  }
  GetNextChar();
  return Token{TokenType::kTokenValueChar, line, col, {n}};
}

Token TokenLoader::StringSplit(const int line, const int col) {
  std::string str;
  while (true) {
    GetNextChar();
    if (current_char_ == '"') {
      break;
    }
    if (current_char_ == '\n') {
      GetNextChar();
      return Token(TokenType::kTokenUnknown, line, col, "EOL in string");
    } else if (current_char_ == EOF) {
      return Token(TokenType::kTokenUnknown, line, col, "EOF in string");
    }
    str += current_char_;
  }

  GetNextChar();
  return Token(TokenType::kTokenValueString, line, col, str);
}

Token TokenLoader::IndentifierOrValue(const int line, const int col) {
  bool is_number = true;
  int count_of_point = 0;

  std::string str;
  // Digits, UpperCase nums, LowerCase nums, '_', '.' are acceptable.
  while (isalnum(current_char_) || current_char_ == '_' ||
         current_char_ == '.') {
    str += current_char_;
    if (isalpha(current_char_) || current_char_ == '_') {
      is_number = false;
    } else if (current_char_ == '.') {
      count_of_point++;
    }
    GetNextChar();
  }
  if (str.empty()) {
    return Token(TokenType::kTokenUnknown, line, col,
                 "unpupported starting charactor" + current_char_);
  }

  if (isdigit(str[0])) {
    if (!is_number) {
      return Token(TokenType::kTokenUnknown, line, col,
                   "unpupported starting charactor" + current_char_);
    }
    if (count_of_point == 0) {
      const int integer_value = std::stoi(str);
      // TODO(edward) if out of range, catch the ex.
      if (errno == ERANGE) {
        return Token(TokenType::kTokenUnknown, line, col,
                     "Number exceeds maximum value: " + str);
      }
      return Token{TokenType::kTokenValueInt, line, col, {integer_value}};
    } else if (count_of_point == 1) {
      const double double_value = std::stod(str);
      return Token{TokenType::kTokenValueDouble, line, col, double_value};
    } else {
      return Token(TokenType::kTokenUnknown, line, col,
                   "invalid double: " + str);
    }
  }
  return Token(GetIdentifierType(str), line, col, str);
}

TokenType TokenLoader::GetIdentifierType(const std::string& text) {
  return kReservedKeywords.count(text) > 0 ? kReservedKeywords.at(text)
                                           : TokenType::kTokenIdentifier;
}

Token TokenLoader::Follow(const char expect, const TokenType is_yes_token,
                          const TokenType is_no_token, const int line,
                          const int col) {
  if (current_char_ == expect) {
    GetNextChar();
    return Token{is_yes_token, line, col, {0}};
  } else if (is_no_token == TokenType::kTokenEOI) {
    return Token(TokenType::kTokenUnknown, line, col,
                 "following unrecognized character: " + current_char_);
  }
  return Token{is_no_token, line, col, {0}};
}

void TokenLoader::Error(const std::string& error_msg) {
  std::cerr << current_line_ << ", " << current_col_ << " error: " << error_msg
            << std::endl;
  exit(1);
}

}  // namespace lex
}  // namespace elsh
