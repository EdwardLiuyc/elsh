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

#include <iostream>
#include <sstream>

#include "lex/token_loader.h"
#include "test/utest_framework/simple_unit_test.h"

namespace elsh {
namespace lex {

SIMPLE_TEST(Lex, EmptyStream) {
  std::stringstream ss;
  TokenLoader loader(&ss);
  const auto tokens = loader.GetAllTokens();
  EXPECT_EQ(1, tokens.size());
  EXPECT_EQ(TokenType::kTokenEOI, tokens[0].tok_type);
}

SIMPLE_TEST(Lex, TypeAndValueTest) {
  {
    std::stringstream ss;
    ss << "int a = 5;\n";
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtInt32, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenValueInt, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
  {
    std::stringstream ss;
    ss << "int64 a = 5;\n";
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtInt64, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenValueInt, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
  {
    std::stringstream ss;
    ss << "char a = 'a';\n";
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtChar, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenValueChar, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
  {
    std::stringstream ss;
    ss << "bool a = true;\n";
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtBool, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenValueBool, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
  {
    std::stringstream ss;
    ss << "string a = \"\";\n";
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtString, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenValueString, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
  {
    std::stringstream ss;
    ss << "double a = 1.2;\n";
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtDouble, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenValueDouble, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
}

SIMPLE_TEST(Lex, Operators) {
  {
    std::stringstream ss;
    ss << "a<b" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenOpLss, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[3].tok_type);
  }
  {
    std::stringstream ss;
    ss << "a>=b" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenOpGeq, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[3].tok_type);
  }
  {
    std::stringstream ss;
    ss << "a||b&&a||c" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(8, tokens.size());
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenOpOr, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAnd, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenOpOr, tokens[5].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[6].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[7].tok_type);
  }
  {
    std::stringstream ss;
    ss << "a%1==0" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(6, tokens.size());
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenOpMod, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenValueInt, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenOpEq, tokens[3].tok_type);
    EXPECT_EQ(TokenType::kTokenValueInt, tokens[4].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[5].tok_type);
  }
}

SIMPLE_TEST(Lex, UnknownTokens) {
  {
    std::stringstream ss;
    ss << "char a = '';" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtChar, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenUnknown, tokens[3].tok_type);
  }
  {
    std::stringstream ss;
    ss << "double a = 1.2.3;" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtDouble, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenOpAssign, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenUnknown, tokens[3].tok_type);
  }
}

SIMPLE_TEST(Lex, Comments) {
  {
    std::stringstream ss;
    ss << "// it's a single line comment.\n" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(1, tokens.size());
    EXPECT_EQ(TokenType::kTokenEOI, tokens[0].tok_type);
  }
  {
    std::stringstream ss;
    ss << "// it's a single line comment.\n double b;" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtDouble, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[3].tok_type);
  }
  {
    std::stringstream ss;
    ss << "/* multiline \n comments */" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(1, tokens.size());
    EXPECT_EQ(TokenType::kTokenEOI, tokens[0].tok_type);
  }
  {
    std::stringstream ss;
    ss << "/* multiline \n comments */ double a;" << std::endl;
    TokenLoader loader(&ss);
    const auto tokens = loader.GetAllTokens();
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ(TokenType::kTokenDtDouble, tokens[0].tok_type);
    EXPECT_EQ(TokenType::kTokenIdentifier, tokens[1].tok_type);
    EXPECT_EQ(TokenType::kTokenSymSemiColon, tokens[2].tok_type);
    EXPECT_EQ(TokenType::kTokenEOI, tokens[3].tok_type);
  }
}
}  // namespace lex
}  // namespace elsh
