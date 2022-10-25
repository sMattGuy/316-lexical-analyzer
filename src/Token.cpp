#include <iostream>
#include <string>

#include "Token.h"
#include "TokenCodes.h"

using namespace std;

Token::Token()
{
  setTokenCode(NAL);
  setLexemeString("");
}

Token::Token(TokenCodes tc, string ls)
{
  setTokenCode(tc);
  setLexemeString(ls);
}

string Token::getLexemeString()
{
  return lexemeString;
}

void Token::setLexemeString(string ls)
{
  lexemeString = ls;
}

TokenCodes Token::getTokenCode()
{
  return tokenCode;
}

void Token::setTokenCode(TokenCodes tc)
{
  tokenCode = tc;
}

ostream& operator<<(ostream& os, const Token& t)
{
  string tcs[] =
  {
    "PLUS", "MINUS", "TIMES", "SLASH", "EQL", "LPAREN", "RPAREN", "PERIOD",
    "COMMA", "SEMICOLON", "COLON", "BECOMES", "LSS", "LEQ", "NEQ", "GTR",
    "GEQ", "ANDSYM", "BEGINSYM", "BOOLSYM", "DIVSYM", "DOSYM", "DOWNTOSYM",
    "ELSESYM", "ENDSYM", "FALSESYM", "FORSYM", "IFSYM", "INTSYM", "MODSYM",
    "NOTSYM", "ORSYM", "PROGSYM", "READSYM", "READLNSYM", "REALSYM",
    "REPEATSYM", "THENSYM", "TOSYM", "TRUESYM", "UNTILSYM", "VARSYM",
    "WHILESYM", "WRITESYM", "WRITELNSYM", "IDENT", "NUMLIT", "EOI", "NAL"
  };

  os << "Next token is: " << tcs[t.tokenCode];
  os << ", lexeme string is \"" << t.lexemeString << "\"";

  return os;
}
