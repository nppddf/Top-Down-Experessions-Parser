#include <stdlib.h>

#include "parser.h"
#include "lexer.h"
#include "parser_structures.h"

void parserInit(Parser *parser, Lexer *lexer) {
    parser->lexer = lexer;
}

void parserExpect(Parser *parser, TokenType tokenType) {
    if (parser->lexer->currentToken.type != tokenType) {
        exit(42);
    }

    lexerGetNextToken(parser->lexer);
}

ULL parseExpression(Parser *parser) {
    ULL leftExpression = parseTerm(parser);
    return parseExpressionPrime(parser, leftExpression);
}

ULL parseExpressionPrime(Parser *parser, ULL accumulator) {
    Token currentToken = parser->lexer->currentToken;
    if (currentToken.type == TOKEN_PLUS) {
        parserExpect(parser, currentToken.type);
        ULL value = parseTerm(parser);
        return parseExpressionPrime(parser, value + accumulator);
    }

    return accumulator;
}

ULL parseTerm(Parser *parser) {
    ULL leftTerm = parseFactor(parser);
    return parseTermPrime(parser, leftTerm);
}

ULL parseTermPrime(Parser *parser, ULL accumulator) {
    Token currentToken = parser->lexer->currentToken;
    if (currentToken.type == TOKEN_MUL) {
        parserExpect(parser, currentToken.type);
        ULL rightTerm = parseFactor(parser);
        return parseTermPrime(parser, rightTerm * accumulator);
    }

    return accumulator;
}

ULL parseFactor(Parser *parser) {
    Token currentToken = parser->lexer->currentToken;
    if (currentToken.type == TOKEN_NUMBER) {
        lexerGetNextToken(parser->lexer);

        return currentToken.value;
    }  
    
    if (currentToken.type == TOKEN_LPAREN) {
        parserExpect(parser, TOKEN_LPAREN);
        ULL value = parseExpression(parser);
        parserExpect(parser, TOKEN_RPAREN);

        return value;
    }

    return 0;
}