#ifndef PARSER_H
#define PARSER_H

#include "parser_structures.h"

void parserInit(Parser *parser, Lexer *lexer);
void parserExpect(Parser *parser, TokenType tokenType);

/* 
 Expr  => Term Expr'
 Expr' => + Term Expr' | eps
 Term  => Fact Term'
 Term' => * Fact Term' | eps
 Fact  => number | '(' Expr ')'
*/

ULL parseExpression(Parser *parser);
ULL parseExpressionPrime(Parser *parser, ULL accumulator);
ULL parseTerm(Parser *parser);
ULL parseTermPrime(Parser *parser, ULL accumulator);
ULL parseFactor(Parser *parser);

#endif // PARSER_H