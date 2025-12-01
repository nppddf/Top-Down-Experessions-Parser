#ifndef LEXER_H
#define LEXER_H

#include "parser_structures.h"

void lexerInit(Lexer *lexer, const char *inputSource);
void lexerGetNextToken(Lexer *lexer);
Token lexerReadNumber(Lexer *lexer);

#endif // LEXER_H