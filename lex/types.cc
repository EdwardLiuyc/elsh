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

#include "lex/types.h"

#include <map>
#include <unordered_map>

namespace elsh {
namespace lex {

const std::unordered_map<TokenType, std::string, EnumClassHash> kTokenNames{
    {TokenType::kTokenEOI, "End_of_input"},
    {TokenType::kTokenUnknown, "Unknown_token"},
    // Operators
    {TokenType::kTokenOpMul, "Op_multiply"},
    {TokenType::kTokenOpDiv, "Op_divide"},
    {TokenType::kTokenOpMod, "Op_mod"},
    {TokenType::kTokenOpAdd, "Op_add"},
    {TokenType::kTokenOpSub, "Op_subtract"},
    {TokenType::kTokenOpNegate, "Op_negate"},
    {TokenType::kTokenOpNot, "Op_not"},
    {TokenType::kTokenOpLss, "Op_less"},
    {TokenType::kTokenOpLeq, "Op_lessequal"},
    {TokenType::kTokenOpGtr, "Op_greater"},
    {TokenType::kTokenOpGeq, "Op_greaterequal"},
    {TokenType::kTokenOpEq, "Op_equal"},
    {TokenType::kTokenOpNeq, "Op_notequal"},
    {TokenType::kTokenOpAssign, "Op_assign"},
    {TokenType::kTokenOpAnd, "Op_and"},
    {TokenType::kTokenOpOr, "Op_or"},
    // Reserved Keywords
    {TokenType::kTokenKwIf, "Keyword_if"},
    {TokenType::kTokenKwElse, "Keyword_else"},
    {TokenType::kTokenKwWhile, "Keyword_while"},
    {TokenType::kTokenKwBreak, "Keyword_break"},
    {TokenType::kTokenKwContinue, "Keyword_continue"},
    {TokenType::kTokenKwDo, "Keyword_do"},
    {TokenType::kTokenKwFor, "Keyword_for"},
    {TokenType::kTokenKwPrint, "Keyword_print"},
    {TokenType::kTokenKwPutc, "Keyword_putc"},
    {TokenType::kTokenKwReturn, "Keyword_return"},
    {TokenType::kTokenKwConst, "Keyword_const"},
    // Symbols
    {TokenType::kTokenSymLparen, "Symbol_LeftParen"},
    {TokenType::kTokenSymRparen, "Symbol_RightParen"},
    {TokenType::kTokenSymLbrace, "Symbol_LeftBrace"},
    {TokenType::kTokenSymRbrace, "Symbol_RightBrace"},
    {TokenType::kTokenSymLbracket, "Symbol_LeftBracket"},
    {TokenType::kTokenSymRbracket, "Symbol_RightBracket"},
    {TokenType::kTokenSymSemiColon, "Symbol_Semicolon"},
    {TokenType::kTokenSymComma, "Symbol_Comma"},
    // Data types
    {TokenType::kTokenDtInt32, "Type_int32"},
    {TokenType::kTokenDtInt64, "Type_int64"},
    {TokenType::kTokenDtUint32, "Type_uint32"},
    {TokenType::kTokenDtUint64, "Type_uint64"},
    {TokenType::kTokenDtDouble, "Type_double"},
    {TokenType::kTokenDtChar, "Type_char"},
    {TokenType::kTokenDtVoid, "Type_void"},
    {TokenType::kTokenDtBool, "Type_bool"},
    {TokenType::kTokenDtString, "Type_string"},

    {TokenType::kTokenIdentifier, "Identifier"},
    {TokenType::kTokenValueInt, "Value_int"},
    {TokenType::kTokenValueDouble, "Value_double"},
    {TokenType::kTokenValueChar, "Value_char"},
    {TokenType::kTokenValueString, "Value_string"},
    {TokenType::kTokenValueBool, "Value_bool"}};

const std::unordered_map<std::string, TokenType> kReservedKeywords{
    {"if", TokenType::kTokenKwIf},
    {"else", TokenType::kTokenKwElse},
    {"while", TokenType::kTokenKwWhile},
    {"break", TokenType::kTokenKwBreak},
    {"continue", TokenType::kTokenKwContinue},
    {"do", TokenType::kTokenKwDo},
    {"for", TokenType::kTokenKwFor},
    {"print", TokenType::kTokenKwPrint},
    {"putc", TokenType::kTokenKwPutc},
    {"return", TokenType::kTokenKwReturn},
    {"const", TokenType::kTokenKwConst},
    {"true", TokenType::kTokenValueBool},
    {"false", TokenType::kTokenValueBool},
    {"int", TokenType::kTokenDtInt32},
    {"int32", TokenType::kTokenDtInt32},
    {"int64", TokenType::kTokenDtInt64},
    {"uint32", TokenType::kTokenDtUint32},
    {"uint64", TokenType::kTokenDtUint64},
    {"double", TokenType::kTokenDtDouble},
    {"char", TokenType::kTokenDtChar},
    {"void", TokenType::kTokenDtVoid},
    {"bool", TokenType::kTokenDtBool},
    {"string", TokenType::kTokenDtString}};

}  // namespace lex
}  // namespace elsh
