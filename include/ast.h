#ifndef AST_H
#define AST_H

#include "tokens.h"

typedef enum {
    NODE_LITERAL,
    NODE_VARIABLE,
    NODE_BINARY,
    NODE_ASSIGN,
    NODE_PRINT
} NodeType;

typedef struct ASTNode {
    NodeType type;
    Token token;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* createNode(NodeType type, Token token);

#endif