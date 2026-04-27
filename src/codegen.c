#include <stdio.h>
#include "ast.h"

void gen(ASTNode* node) {
    if (node == NULL) return;

    switch (node->type) {
        case NODE_LITERAL:
            printf("  push %.*s\n", node->token.length, node->token.start);
            break;
        case NODE_BINARY:
            gen(node->left);
            gen(node->right);
            printf("  pop rdi\n  pop rax\n");
            if (node->token.type == TOKEN_PLUS) printf("  add rax, rdi\n");
            else if (node->token.type == TOKEN_MINUS) printf("  sub rax, rdi\n");
            else if (node->token.type == TOKEN_STAR) printf("  imul rax, rdi\n");
            printf("  push rax\n");
            break;
        case NODE_PRINT:
            gen(node->left);
            printf("  pop rdi\n  call print_num\n");
            break;
        case NODE_ASSIGN:
            gen(node->right);
            printf("  pop rax\n  mov [%.*s], rax\n", node->token.length, node->left->token.start);
            break;
        default: break;
    }
    if (node->next) gen(node->next);
}