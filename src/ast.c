#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

static ASTNode *createASTNode(void) {
    ASTNode *node = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (node == NULL) {
        printf("Failed to allocate the memory for AST node.\n");
        exit(EXIT_FAILURE);
    }
    return node;
}

ASTNode *createNumberASTNode(int value) {
    ASTNode *node = createASTNode();
    node->type = AST_NUMBER;
    node->data.value = value;
    return node;
}

ASTNode *createOperatorASTNode(AstNodeType type, ASTNode *left, ASTNode *right) {
    // TODO: Add pointer transfer check
    ASTNode *node = createASTNode();
    node->type = type;
    node->data.operands.left = left;
    node->data.operands.right = right;
    return node;
}

void freeASTNode(ASTNode *node) {
    if (node == NULL) {
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
    node = NULL;
}

void printASTNode(const ASTNode *node) {
    if (node == NULL) {
        return;
    }

    printf("Result: %lu\n", evaluateAST(node));
}

unsigned long evaluateAST(const ASTNode *node) {
    // TODO: Add pointer transfer check

    if (node == NULL) {
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