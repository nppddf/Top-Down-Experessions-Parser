#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct {
    Lexer *lexer;
    int error;
    const char *errorMessage;
} Parser;

void initializeParser(Parser *parser, Lexer *lexer);
void printErrorParser(Parser *parser);
AstNode *parserParse(Parser *parser);

#endif // PARSER_H
