#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct {
    Lexer *lexer;
    int isError;
    const char *errorMessage;
} Parser;

int initializeParser(Parser *parser, Lexer *lexer);
int printErrorParser(Parser *parser);
ASTNode *parserParse(Parser *parser);

#endif // PARSER_H
