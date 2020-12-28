// Copyright

#include <libio.h>
#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "lex/token_loader.h"

using lex::kTokenNames;
using lex::Token;
using lex::TokenType;

int main(int argc, char** argv) {
  if (argc < 2) {
    return -1;
  }

  lex::TokenLoader loader(argv[1]);
  Token tok;
  do {
    tok = loader.GetToken();
    std::cout << "\t" << tok.err_ln << "\t" << tok.err_col << "\t"
              << kTokenNames.at(tok.tok_type);

    switch (tok.tok_type) {
      case TokenType::kTokenValueInt:
        std::cout << "\t" << tok.n;
        break;
      case TokenType::kTokenValudChar:
        std::cout << "\t" << static_cast<int>(tok.text);
        break;
      case TokenType::kTokenIdentifier:
      case TokenType::kTokenValueString:
        std::cout << "\t" << tok.str;
        break;

      default:
        break;
    }
    std::cout << "\n" << std::flush;
  } while (tok.tok_type != TokenType::kTokenEOI);

  return 0;
}
