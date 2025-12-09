#include <ctype.h>
#include <stdlib.h>

#include "lexer.h"
#include "utils.h"

static Token createToken(TokenType type, int value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

int initializeLexer(Lexer *lexer, const char *input) {
    SOFT_ASSERT(lexer != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);
    SOFT_ASSERT(input != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);

    lexer->input = input;
    lexer->position = 0;
    lexer->hasCurrentToken = 0;

    return EXIT_SUCCESS;
}

static Token lexerReadToken(Lexer *lexer) {
    SOFT_ASSERT(lexer != NULL, "Failed to transfer a pointer.\n", (Token){.type = TOKEN_INVALID});

    const char *string = lexer->input;
    unsigned long currentIndex = lexer->position;

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
    SOFT_ASSERT(lexer != NULL, "Failed to transfer a pointer.\n", (Token){.type = TOKEN_INVALID});

    if (!lexer->hasCurrentToken) {
        lexer->current = lexerReadToken(lexer);
        lexer->hasCurrentToken = 1;
    }
    return lexer->current;
}

Token lexerNext(Lexer *lexer) {
    SOFT_ASSERT(lexer != NULL, "Failed to transfer a pointer.\n", (Token){.type = TOKEN_INVALID});

    if (lexer->hasCurrentToken) {
        lexer->hasCurrentToken = 0;
        return lexer->current;
    }
    return lexerReadToken(lexer);
}
