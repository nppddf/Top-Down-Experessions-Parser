#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ast.h"
#include "utils.h"

static ASTNode *createASTNode(void) {
    ASTNode *node = calloc(1, sizeof(ASTNode));
    SOFT_ASSERT(node != NULL, "Failed to allocate the memory.\n", NULL);

    return node;
}

ASTNode *createNumberASTNode(int value) {
    ASTNode *node = createASTNode();
    node->type = AST_NUMBER;
    node->data.value = value;
    return node;
}

ASTNode *createOperatorASTNode(AstNodeType type, ASTNode *left, ASTNode *right) {
    SOFT_ASSERT(left != NULL, "Failed to transfer a pointer.\n", NULL);
    SOFT_ASSERT(right != NULL, "Failed to transfer a pointer.\n", NULL);

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

int printASTResult(const ASTNode *node) {
    SOFT_ASSERT(node != NULL, "Failed to transfer a pointer.\n", EXIT_FAILURE);

    ssize_t result = evaluateAST(node);
    SOFT_ASSERT(result != -1, "Failed to evaluate the AST.\n", EXIT_FAILURE);

    printf("Result: %lu\n", result);

    return EXIT_SUCCESS;
}

ssize_t evaluateAST(const ASTNode *node) {
    SOFT_ASSERT(node != NULL, "Failed to transfer a pointer.\n", -1);

    if (node->type == AST_NUMBER) {
        return node->data.value;
    }

    ssize_t left = evaluateAST(node->data.operands.left);
    ssize_t right = evaluateAST(node->data.operands.right);
    switch (node->type) {
    case AST_ADD: {
        return left + right;
    }
    case AST_MUL: {
        return left * right;
    }
    default: {
        SOFT_ASSERT(false, "Failed to define node type.\n", -1);
    }
    }
}
