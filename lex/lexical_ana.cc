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

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "lex/token_loader.h"

using elsh::lex::kTokenNames;
using elsh::lex::Token;
using elsh::lex::TokenType;

int main(int argc, char** argv) {
  if (argc < 2) {
    return -1;
  }

  elsh::lex::TokenLoader loader(argv[1]);
  Token tok;
  do {
    tok = loader.GetToken();
    std::cout << "\t" << tok.err_ln << "\t" << tok.err_col << "\t"
              << kTokenNames.at(tok.tok_type);

    switch (tok.tok_type) {
      case TokenType::kTokenValueInt:
        std::cout << "\t" << tok.value_int;
        break;
      case TokenType::kTokenValudChar:
        std::cout << "\t" << static_cast<int>(tok.value_char);
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
