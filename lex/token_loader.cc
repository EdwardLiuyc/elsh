// Copyright

#include "lex/token_loader.h"

#include <iostream>
#include <unordered_map>

namespace lex {
namespace {

const std::unordered_map<char, TokenType> kSimpleTokenMap{
    {'{', TokenType::tk_Lbrace}, {'}', TokenType::tk_Rbrace},
    {'(', TokenType::tk_Lparen}, {')', TokenType::tk_Rparen},
    {'+', TokenType::tk_Add},    {'-', TokenType::tk_Sub},
    {'*', TokenType::tk_Mul},    {'%', TokenType::tk_Mod},
    {';', TokenType::tk_Semi},   {',', TokenType::tk_Comma}};
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
        return Follow('=', TokenType::tk_Leq, TokenType::tk_Lss, start_line,
                      start_col);
      case '>':
        GetNextChar();
        return Follow('=', TokenType::tk_Geq, TokenType::tk_Gtr, start_line,
                      start_col);
      case '=':
        GetNextChar();
        return Follow('=', TokenType::tk_Eq, TokenType::tk_Assign, start_line,
                      start_col);
      case '!':
        GetNextChar();
        return Follow('=', TokenType::tk_Neq, TokenType::tk_Not, start_line,
                      start_col);
      case '&':
        GetNextChar();
        return Follow('&', TokenType::tk_And, TokenType::tk_EOI, start_line,
                      start_col);
      case '|':
        GetNextChar();
        return Follow('|', TokenType::tk_Or, TokenType::tk_EOI, start_line,
                      start_col);
      case '"':
        return StringSplit(start_line, start_col);
      case EOF:
        return Token{TokenType::tk_EOI, start_line, start_col, {0}};
      default:
        return IndentifierOrInteger(start_line, start_col);
    }
  }
}

void TokenLoader::GetNextChar() {
  last_char_ = current_char_;
  if (source_fs_.get(current_char_)) {
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
    return Token{TokenType::tk_Div, line, col, {0}};
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
      Error("EOF in comment");
    } else {
      GetNextChar();
    }
  }
}

Token TokenLoader::CharSplit(const int line, const int col) {
  if (current_char_ == '\'') {
    Error("empty character constant");
  }

  int n = current_char_;
  if (current_char_ == '\\') {
    GetNextChar();
    if (current_char_ == 'n') {
      n = '\n';
    } else if (current_char_ == '\\') {
      n = '\\';
    } else {
      Error("gettok: unknown escape sequence \\" + current_char_);
    }
  }

  GetNextChar();
  if (current_char_ != '\'') {
    Error("multi-character constant");
  }
  GetNextChar();
  return Token{TokenType::tk_Integer, line, col, {n}};
}

Token TokenLoader::StringSplit(const int line, const int col) {
  std::string str;
  while (true) {
    GetNextChar();
    if (current_char_ == '"') {
      break;
    }
    if (current_char_ == '\n') Error("EOL in string");
    if (current_char_ == EOF) Error("EOF in string");

    str += current_char_;
  }

  GetNextChar();
  return Token(TokenType::tk_String, line, col, str);
}

Token TokenLoader::IndentifierOrInteger(const int line, const int col) {
  int n;
  bool is_number = true;

  std::string str;
  // Digits, UpperCase nums, LowerCase nums, '_', '.' are acceptable.
  while (isalnum(current_char_) || current_char_ == '_' ||
         current_char_ == '.') {
    str += current_char_;
    if (isalpha(current_char_) || current_char_ == '_') {
      is_number = false;
    }
    GetNextChar();
  }
  if (str.empty()) {
    Error("gettok: unrecognized character  " + current_char_);
  }

  if (isdigit(str[0])) {
    if (!is_number) {
      Error("invalid number: " + str);
    }
    n = std::stoi(str);
    if (errno == ERANGE) Error("Number exceeds maximum value");
    return Token{TokenType::tk_Integer, line, col, {n}};
  }
  return Token(GetIdentifierType(str), line, col, str);
}

TokenType TokenLoader::GetIdentifierType(const std::string& text) {
  const std::unordered_map<std::string, TokenType> inner_identifiers{
      {"else", TokenType::tk_Else},   {"if", TokenType::tk_If},
      {"print", TokenType::tk_Print}, {"putc", TokenType::tk_Putc},
      {"while", TokenType::tk_While}, {"do", TokenType::tk_Do}};

  return inner_identifiers.count(text) > 0 ? inner_identifiers.at(text)
                                           : TokenType::tk_Ident;
}

Token TokenLoader::Follow(const char expect, const TokenType is_yes_token,
                          const TokenType is_no_token, const int line,
                          const int col) {
  if (current_char_ == expect) {
    GetNextChar();
    return Token{is_yes_token, line, col, {0}};
  } else if (is_no_token == TokenType::tk_EOI) {
    Error("Follow: unrecognized character " + current_char_);
  }
  return Token{is_no_token, line, col, {0}};
}

void TokenLoader::Error(const std::string& error_msg) {
  std::cerr << current_line_ << ", " << current_col_ << " error: " << error_msg
            << std::endl;
  exit(1);
}

}  // namespace lex
