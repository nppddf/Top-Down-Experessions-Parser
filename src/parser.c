#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static ASTNode *parseExpression(Parser *parser);
static ASTNode *parseTerm(Parser *parser);
static ASTNode *parseFactor(Parser *parser);

static int parserSetError(Parser *parser, const char *message) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);

    if (!parser->isError) {
        parser->isError = true;
        parser->errorMessage = message;
    }

    return EXIT_SUCCESS;
}

int printErrorParser(Parser *parser) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);

    printf("Parse isError: %s\n", parser->errorMessage ? parser->errorMessage : "unknown");

    return EXIT_SUCCESS;
}

int initializeParser(Parser *parser, Lexer *lexer) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);
    SOFT_ASSERT(lexer != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);

    parser->lexer = lexer;
    parser->isError = false;
    parser->errorMessage = NULL;

    return EXIT_SUCCESS;
}

ASTNode *parserParse(Parser *parser) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", NULL);

    ASTNode *root = parseExpression(parser);
    SOFT_ASSERT(root != NULL, "Failed to parse the expression.\n", NULL);

    if (parser->isError) {
        if (root) {
            freeASTNode(root);
        }
        return NULL;
    }

    Token token = lexerPeek(parser->lexer);
    if (token.type != TOKEN_END) {
        parserSetError(parser, "Unexpected characters after expression");
        if (root) {
            freeASTNode(root);
        }
        return NULL;
    }

    return root;
}

static ASTNode *parseExpression(Parser *parser) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", NULL);

    ASTNode *left = parseTerm(parser);
    if (parser->isError || left == NULL) {
        return NULL;
    }

    while (!parser->isError) {
        Token token = lexerPeek(parser->lexer);

        if (token.type == TOKEN_PLUS) {
            lexerNext(parser->lexer);

            ASTNode *right = parseTerm(parser);
            if (right == NULL) {
                freeASTNode(left);
                return NULL;
            }

            left = createOperatorASTNode(AST_ADD, left, right);
        } else if (token.type == TOKEN_INVALID) {
            parserSetError(parser, "Invalid token in expression");
            freeASTNode(left);
            return NULL;
        } else {
            break;
        }
    }

    return left;
}

static ASTNode *parseTerm(Parser *parser) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", NULL);

    ASTNode *left = parseFactor(parser);
    if (parser->isError || left == NULL) {
        return NULL;
    }

    while (!parser->isError) {
        Token token = lexerPeek(parser->lexer);

        if (token.type == TOKEN_STAR) {
            lexerNext(parser->lexer);

            ASTNode *right = parseFactor(parser);
            if (right == NULL) {
                freeASTNode(left);
                return NULL;
            }

            left = createOperatorASTNode(AST_MUL, left, right);
        } else if (token.type == TOKEN_INVALID) {
            parserSetError(parser, "Invalid token in term");
            freeASTNode(left);
            return NULL;
        } else {
            break;
        }
    }

    return left;
}

static ASTNode *parseFactor(Parser *parser) {
    SOFT_ASSERT(parser != NULL, "Failed to transfer a pointer.\n", NULL);

    Token token = lexerPeek(parser->lexer);

    if (token.type == TOKEN_NUMBER) {
        lexerNext(parser->lexer);
        return createNumberASTNode(token.value);
    }

    if (token.type == TOKEN_LPAREN) {
        lexerNext(parser->lexer);

        ASTNode *inside = parseExpression(parser);
        if (parser->isError || !inside) {
            return NULL;
        }

        Token token2 = lexerPeek(parser->lexer);
        if (token2.type != TOKEN_RPAREN) {
            parserSetError(parser, "Expected ')'");
            freeASTNode(inside);
            return NULL;
        }

        lexerNext(parser->lexer);
        return inside;
    }

    if (token.type == TOKEN_INVALID) {
        parserSetError(parser, "Invalid token in factor");
    } else {
        parserSetError(parser, "Expected number or '('");
    }

    return NULL;
}
