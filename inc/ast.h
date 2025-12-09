#ifndef AST_H
#define AST_H

#include <sys/types.h>

typedef enum { AST_NUMBER, AST_ADD, AST_MUL } AstNodeType;

typedef struct ASTNode {
    AstNodeType type;
    union {
        int value;
        struct {
            struct ASTNode *left;
            struct ASTNode *right;
        } operands;
    } data;
} ASTNode;

ASTNode *createNumberASTNode(int value);
ASTNode *createOperatorASTNode(AstNodeType type, ASTNode *left, ASTNode *right);

void freeASTNode(ASTNode *node);
int printASTResult(const ASTNode *node);
ssize_t evaluateAST(const ASTNode *node);

#endif // AST_H
