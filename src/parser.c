#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include <stdio.h>

static AstNode *parseExpression(Parser *parser);
static AstNode *parseTerm(Parser *parser);
static AstNode *parseFactor(Parser *parser);

static void parsesSetError(Parser *parser, const char *message) {
    // TODO: Add pointer transfer check
    if (!parser->error) {
        parser->error = 1;
        parser->errorMessage = message;
    }
}

void printErrorParser(Parser *parser) {
    // TODO: Add pointer transfer check
    printf("Parse error: %s\n", parser->errorMessage ? parser->errorMessage : "(unknown)");
}

void initializeParser(Parser *parser, Lexer *lexer) {
    // TODO: Add pointer transfer check
    parser->lexer = lexer;
    parser->error = 0;
    parser->errorMessage = NULL;
}

AstNode *parserParse(Parser *parser) {
    // TODO: Add pointer transfer check
    AstNode *root = parseExpression(parser);

    if (parser->error) {
        if (root) {
            freeASTNode(root);
        }
        return NULL;
    }

    Token token = lexerPeek(parser->lexer);
    if (token.type != TOKEN_END) {
        parsesSetError(parser, "Unexpected characters after expression");
        if (root) {
            freeASTNode(root);
        }
        return NULL;
    }

    return root;
}

static AstNode *parseExpression(Parser *parser) {
    // TODO: Add pointer transfer check
    AstNode *left = parseTerm(parser);
    if (parser->error || !left) {
        return NULL;
    }

    while (!parser->error) {
        Token token = lexerPeek(parser->lexer);

        if (token.type == TOKEN_PLUS) {
            lexerNext(parser->lexer);

            AstNode *right = parseTerm(parser);
            if (!right) {
                freeASTNode(left);
                return NULL;
            }

            left = createOperatorASTNode(AST_ADD, left, right);
        } else if (token.type == TOKEN_INVALID) {
            parsesSetError(parser, "Invalid Token in expression");
            freeASTNode(left);
            return NULL;
        } else {
            break;
        }
    }

    return left;
}

static AstNode *parseTerm(Parser *parser) {
    // TODO: Add pointer transfer check
    AstNode *left = parseFactor(parser);
    if (parser->error || !left) {
        return NULL;
    }

    while (!parser->error) {
        Token token = lexerPeek(parser->lexer);

        if (token.type == TOKEN_STAR) {
            lexerNext(parser->lexer);

            AstNode *right = parseFactor(parser);
            if (!right) {
                freeASTNode(left);
                return NULL;
            }

            left = createOperatorASTNode(AST_MUL, left, right);
        } else if (token.type == TOKEN_INVALID) {
            parsesSetError(parser, "Invalid Token in term");
            freeASTNode(left);
            return NULL;
        } else {
            break;
        }
    }

    return left;
}

static AstNode *parseFactor(Parser *parser) {
    // TODO: Add pointer transfer check
    Token token = lexerPeek(parser->lexer);

    if (token.type == TOKEN_NUMBER) {
        lexerNext(parser->lexer);
        return createNumberASTNode(token.value);
    }

    if (token.type == TOKEN_LPAREN) {
        lexerNext(parser->lexer);

        AstNode *inside = parseExpression(parser);
        if (parser->error || !inside) {
            return NULL;
        }

        Token token2 = lexerPeek(parser->lexer);
        if (token2.type != TOKEN_RPAREN) {
            parsesSetError(parser, "Expected ')'");
            freeASTNode(inside);
            return NULL;
        }

        lexerNext(parser->lexer);
        return inside;
    }

    if (token.type == TOKEN_INVALID) {
        parsesSetError(parser, "Invalid Token in factor");
    } else {
        parsesSetError(parser, "Expected number or '('");
    }

    return NULL;
}
