#include <ctype.h>

#include "lexer.h"
#include "parser_structures.h"

void lexerInit(Lexer *lexer, const char *inputSource) {
    lexer->inputPointer = inputSource;
    lexer->inputPointerPosition = 0;
    lexerGetNextToken(lexer);
}

void lexerGetNextToken(Lexer *lexer) {
    while (isspace(lexer->inputPointer[lexer->inputPointerPosition])) {
        lexer->inputPointerPosition++;
    }

    Token newToken = {TOKEN_JUNK, 0};
    char currentChar = lexer->inputPointer[lexer->inputPointerPosition];
    if (currentChar == '\0') {
        newToken.type = TOKEN_END;
    } else if (isdigit(currentChar)) {
        newToken = lexerReadNumber(lexer);
    } else {
        lexer->inputPointerPosition++;
        switch (currentChar) {
        case '+': {
            newToken.type = TOKEN_PLUS;
            break;
        }
        case '*': {
            newToken.type = TOKEN_MUL;
            break;
        }
        case '(': {
            newToken.type = TOKEN_LPAREN;
            break;
        }
        case ')': {
            newToken.type = TOKEN_RPAREN;
            break;
        }
        default: {
            newToken.type = TOKEN_JUNK;
            break;
        }
        }
    }

    lexer->currentToken = newToken;
}

Token lexerReadNumber(Lexer *lexer) {
    ULL value = 0;
    while (isdigit(lexer->inputPointer[lexer->inputPointerPosition])) {
        value = value * 10 + (lexer->inputPointer[lexer->inputPointerPosition] - '0');
        lexer->inputPointerPosition++;
    }

    Token numberToken = {TOKEN_JUNK, 0};
    numberToken.type = TOKEN_NUMBER;
    numberToken.value = value;

    return numberToken;
}