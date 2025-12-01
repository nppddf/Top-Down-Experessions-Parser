#ifndef PARSER_STRUCTURES_H
#define PARSER_STRUCTURES_H

#include <stddef.h>

typedef unsigned long long ULL;

typedef enum {
    TOKEN_JUNK,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MUL,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END
} TokenType;

typedef struct {
    TokenType type;
    ULL value;
} Token;

typedef struct {
    Token currentToken;
    const char *inputPointer;
    size_t inputPointerPosition;
} Lexer;

typedef struct {
    Lexer *lexer;
} Parser;
 
#endif // PARSER_STRUCTURES_H