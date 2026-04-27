#include <stdlib.h>
#include "ast.h"

ASTNode* createNode(NodeType type, Token token) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}