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

#ifndef LEX_TYPES_H_
#define LEX_TYPES_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace lex {

enum class TokenType : uint16_t {
  kTokenEOI = 0,

  // Operators
  kTokenOpMul = 100,
  kTokenOpDiv = 101,
  kTokenOpMod = 102,
  kTokenOpAdd = 103,
  kTokenOpSub = 104,
  kTokenOpNegate = 105,
  kTokenOpNot = 106,
  kTokenOpLss = 107,
  kTokenOpLeq = 108,
  kTokenOpGtr = 109,
  kTokenOpGeq = 110,
  kTokenOpEq = 111,
  kTokenOpNeq = 112,
  kTokenOpAssign = 113,
  kTokenOpAnd = 114,
  kTokenOpOr = 115,

  // Reserved Keywords
  kTokenKwIf = 200,
  kTokenKwElse = 201,
  kTokenKwWhile = 202,
  kTokenKwBreak = 203,
  kTokenKwContinue = 204,
  kTokenKwDo = 205,
  kTokenKwFor = 206,
  kTokenKwPrint = 207,
  kTokenKwPutc = 208,
  kTokenKwReturn = 209,
  kTokenKwConst = 210,

  // Symbols
  kTokenSymLparen = 300,
  kTokenSymRparen = 301,
  kTokenSymLbrace = 302,
  kTokenSymRbrace = 303,
  kTokenSymLbracket = 304,
  kTokenSymRbracket = 305,
  kTokenSymSemiColon = 306,
  kTokenSymComma = 307,

  // Data types
  kTokenDtInt32 = 400,
  kTokenDtInt64 = 401,
  kTokenDtUint32 = 402,
  kTokenDtUint64 = 403,
  kTokenDtDouble = 404,
  kTokenDtChar = 405,
  kTokenDtVoid = 407,
  kTokenDtBool = 408,
  kTokenDtString = 409,

  // Others
  kTokenIdentifier = 500,
  kTokenValueInt = 501,
  kTokenValueDouble = 502,
  kTokenValudChar = 503,
  kTokenValueString = 504,
  kTokenValueBool = 505,
};

// Enum class can not be use as `unordered_map` key in c++11, so we define our
// own hash function for enum classes.
struct EnumClassHash {
  template <typename T>
  std::size_t operator()(const T& t) const {
    return static_cast<std::size_t>(t);
  }
};

extern const std::unordered_map<TokenType, std::string, EnumClassHash>
    kTokenNames;
extern const std::unordered_map<std::string, TokenType> kReservedKeywords;

struct Token {
  Token() = default;
  Token(TokenType type, const int line, const int col)
      : tok_type(type), err_ln(line), err_col(col) {}
  Token(TokenType type, const int line, const int col, const std::string& s)
      : tok_type(type), err_ln(line), err_col(col), str(s) {}
  Token(TokenType type, const int line, const int col, const int int_value)
      : tok_type(type), err_ln(line), err_col(col), value_int(int_value) {}
  Token(TokenType type, const int line, const int col, const char char_value)
      : tok_type(type), err_ln(line), err_col(col), value_char(char_value) {}

  TokenType tok_type;

  int err_ln;
  int err_col;
  std::string str = "";
  // value for constants
  union {
    int64_t value_int;
    double value_double;
    char value_char;
    bool value_bool;
  };
};

}  // namespace lex

#endif  // LEX_TYPES_H_
