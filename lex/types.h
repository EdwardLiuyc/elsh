// Copyright

#ifndef LEX_TYPES_H_
#define LEX_TYPES_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace lex {

enum class TokenType : uint8_t {
  tk_EOI,
  tk_Mul,
  tk_Div,
  tk_Mod,
  tk_Add,
  tk_Sub,
  tk_Negate,
  tk_Not,
  tk_Lss,
  tk_Leq,
  tk_Gtr,
  tk_Geq,
  tk_Eq,
  tk_Neq,
  tk_Assign,
  tk_And,
  tk_Or,
  tk_If,
  tk_Else,
  tk_While,
  tk_Do,
  tk_Print,
  tk_Putc,
  tk_Lparen,
  tk_Rparen,
  tk_Lbrace,
  tk_Rbrace,
  tk_Semi,
  tk_Comma,
  tk_Ident,
  tk_Integer,
  tk_Double,
  tk_String
};

extern const std::map<TokenType, std::string> TokenNames;

struct Token {
  Token() = default;
  Token(TokenType type, const int line, const int col)
      : tok_type(type), err_ln(line), err_col(col) {}
  Token(TokenType type, const int line, const int col, const std::string& s)
      : tok_type(type), err_ln(line), err_col(col), str(s) {}
  Token(TokenType type, const int line, const int col, const int int_value)
      : tok_type(type), err_ln(line), err_col(col), n(int_value) {}
  Token(TokenType type, const int line, const int col, const char char_value)
      : tok_type(type), err_ln(line), err_col(col), text(char_value) {}

  TokenType tok_type;

  int err_ln;
  int err_col;
  std::string str = "";
  // Vaules
  union {
    int n; /* value for constants */
    char text;
  };
};

}  // namespace lex

#endif  // LEX_TYPES_H_
