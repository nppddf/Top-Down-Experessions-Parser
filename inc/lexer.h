#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_STAR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    int value;
} Token;

typedef struct {
    const char *input;
    unsigned long position;
    Token current;
    int hasCurrentToken;
} Lexer;

int initializeLexer(Lexer *lexer, const char *input);
Token lexerNext(Lexer *lexer);
Token lexerPeek(Lexer *lexer);

#endif // LEXER_H
