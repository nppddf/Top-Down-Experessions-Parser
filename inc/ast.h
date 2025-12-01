#ifndef AST_H
#define AST_H

typedef enum { AST_NUMBER, AST_ADD, AST_MUL } AstNodeType;

typedef struct AstNode {
    AstNodeType type;
    union {
        int value;
        struct {
            struct AstNode *left;
            struct AstNode *right;
        } operands;
    } data;
} AstNode;

AstNode *createNumberASTNode(int value);
AstNode *createOperatorASTNode(AstNodeType type, AstNode *left, AstNode *right);

void freeASTNode(AstNode *node);
void printASTNode(const AstNode *node);
unsigned long evaluateAST(const AstNode *node);

#endif // AST_H
