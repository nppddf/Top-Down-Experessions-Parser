#include "lexer.h"
#include <ctype.h>

static Token createToken(TokenType type, int value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

void initializeLexer(Lexer *lexer, const char *input) {
    // TODO: Add pointer transfer check
    lexer->input = input;
    lexer->position = 0;
    lexer->hasCurrentToken = 0;
}

static Token lexerReadToken(Lexer *lexer) {
    // TODO: Add pointer transfer check
    const char *string = lexer->input;
    unsigned long currentIndex = lexer->position;

    // TODO: Make Skip spaces function
    while (string[currentIndex] != '\0' && isspace(string[currentIndex])) {
        currentIndex++;
    }

    if (string[currentIndex] == '\0') {
        lexer->position = currentIndex;
        return createToken(TOKEN_END, 0);
    }

    char currentCharacter = string[currentIndex];

    if (isdigit(currentCharacter)) {
        int value = 0;
        while (isdigit(string[currentIndex])) {
            // TODO: Make toDigit function
            value = value * 10 + (string[currentIndex] - '0');
            currentIndex++;
        }
        lexer->position = currentIndex;
        return createToken(TOKEN_NUMBER, value);
    }

    lexer->position = currentIndex + 1;
    switch (currentCharacter) {
    case '+':
        return createToken(TOKEN_PLUS, 0);
    case '*':
        return createToken(TOKEN_STAR, 0);
    case '(':
        return createToken(TOKEN_LPAREN, 0);
    case ')':
        return createToken(TOKEN_RPAREN, 0);
    default:
        return createToken(TOKEN_INVALID, 0);
    }
}

Token lexerPeek(Lexer *lexer) {
    // TODO: Add pointer transfer check
    if (!lexer->hasCurrentToken) {
        lexer->current = lexerReadToken(lexer);
        lexer->hasCurrentToken = 1;
    }
    return lexer->current;
}

Token lexerNext(Lexer *lexer) {
    // TODO: Add pointer transfer check
    if (lexer->hasCurrentToken) {
        lexer->hasCurrentToken = 0;
        return lexer->current;
    }
    return lexerReadToken(lexer);
}
