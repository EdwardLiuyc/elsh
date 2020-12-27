// Copyright

#include "lex/types.h"

#include <map>

namespace lex {

const std::map<TokenType, std::string> TokenNames{
    {TokenType::tk_EOI, "End_of_input"},
    {TokenType::tk_Mul, "Op_multiply"},
    {TokenType::tk_Div, "Op_divide"},
    {TokenType::tk_Mod, "Op_mod"},
    {TokenType::tk_Add, "Op_add"},
    {TokenType::tk_Sub, "Op_subtract"},
    {TokenType::tk_Negate, "Op_negate"},
    {TokenType::tk_Not, "Op_not"},
    {TokenType::tk_Lss, "Op_less"},
    {TokenType::tk_Leq, "Op_lessequal"},
    {TokenType::tk_Gtr, "Op_greater"},
    {TokenType::tk_Geq, "Op_greaterequal"},
    {TokenType::tk_Eq, "Op_equal"},
    {TokenType::tk_Neq, "Op_notequal"},
    {TokenType::tk_Assign, "Op_assign"},
    {TokenType::tk_And, "Op_and"},
    {TokenType::tk_Or, "Op_or"},
    {TokenType::tk_If, "Keyword_if"},
    {TokenType::tk_Else, "Keyword_else"},
    {TokenType::tk_While, "Keyword_while"},
    {TokenType::tk_Do, "Keyword_do"},
    {TokenType::tk_Print, "Keyword_print"},
    {TokenType::tk_Putc, "Keyword_putc"},
    {TokenType::tk_Lparen, "LeftParen"},
    {TokenType::tk_Rparen, "RightParen"},
    {TokenType::tk_Lbrace, "LeftBrace"},
    {TokenType::tk_Rbrace, "RightBrace"},
    {TokenType::tk_Semi, "Semicolon"},
    {TokenType::tk_Comma, "Comma"},
    {TokenType::tk_Ident, "Identifier"},
    {TokenType::tk_Integer, "Integer"},
    {TokenType::tk_Double, "Double"},
    {TokenType::tk_String, "String"},
};

}  // namespace lex
