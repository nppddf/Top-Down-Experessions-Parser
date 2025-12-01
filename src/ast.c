#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

static AstNode *createASTNode(void) {
    AstNode *node = (AstNode *)calloc(1, sizeof(AstNode));
    if (!node) {
        printf("Failed to allocate the memory for AST node.\n");
        exit(EXIT_FAILURE);
    }
    return node;
}

AstNode *createNumberASTNode(int value) {
    AstNode *node = createASTNode();
    node->type = AST_NUMBER;
    node->data.value = value;
    return node;
}

AstNode *createOperatorASTNode(AstNodeType type, AstNode *left, AstNode *right) {
    // TODO: Add pointer transfer check
    AstNode *node = createASTNode();
    node->type = type;
    node->data.operands.left = left;
    node->data.operands.right = right;
    return node;
}

void freeASTNode(AstNode *node) {
    if (!node) {
        return;
    }

    switch (node->type) {
    case AST_NUMBER:
        break;
    case AST_ADD:
    case AST_MUL:
        freeASTNode(node->data.operands.left);
        freeASTNode(node->data.operands.right);
        break;
    default:
        break;
    }

    free(node);
}

void printASTNode(const AstNode *node) {
    if (!node) {
        return;
    }

    printf("Result: %lu\n", evaluateAST(node));
}

unsigned long evaluateAST(const AstNode *node) {
    // TODO: Add pointer transfer check

    if (!node) {
        return 0U;
    }

    switch (node->type) {
    case AST_NUMBER: {
        return node->data.value;
    }
    case AST_ADD: {
        unsigned long left = evaluateAST(node->data.operands.left);
        unsigned long right = evaluateAST(node->data.operands.right);
        return left + right;
    }
    case AST_MUL: {
        unsigned long left = evaluateAST(node->data.operands.left);
        unsigned long right = evaluateAST(node->data.operands.right);
        return left * right;
    }
    default: {
        return 0;
    }
    }
}