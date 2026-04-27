#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

Parser parser;

static void advance() {
    parser.previous = parser.current;
    parser.current = scanToken();
}

static ASTNode* expression();

static ASTNode* primary() {
    if (parser.current.type == TOKEN_NUMBER) {
        advance();
        return createNode(NODE_LITERAL, parser.previous);
    }
    if (parser.current.type == TOKEN_IDENTIFIER) {
        advance();
        return createNode(NODE_VARIABLE, parser.previous);
    }
    return NULL;
}

static ASTNode* term() {
    ASTNode* node = primary();
    while (parser.current.type == TOKEN_STAR || parser.current.type == TOKEN_SLASH) {
        Token op = parser.current;
        advance();
        ASTNode* new_node = createNode(NODE_BINARY, op);
        new_node->left = node;
        new_node->right = primary();
        node = new_node;
    }
    return node;
}

static ASTNode* expression() {
    ASTNode* node = term();
    while (parser.current.type == TOKEN_PLUS || parser.current.type == TOKEN_MINUS) {
        Token op = parser.current;
        advance();
        ASTNode* new_node = createNode(NODE_BINARY, op);
        new_node->left = node;
        new_node->right = term();
        node = new_node;
    }
    return node;
}

static ASTNode* statement() {
    if (parser.current.type == TOKEN_PRINT) {
        advance();
        ASTNode* node = createNode(NODE_PRINT, parser.previous);
        node->left = expression();
        if (parser.current.type == TOKEN_SEMICOLON) advance();
        return node;
    }
    ASTNode* node = expression();
    if (node->type == NODE_VARIABLE && parser.current.type == TOKEN_EQUAL) {
        Token op = parser.current;
        advance();
        ASTNode* assignNode = createNode(NODE_ASSIGN, op);
        assignNode->left = node;
        assignNode->right = expression();
        node = assignNode;
    }
    if (parser.current.type == TOKEN_SEMICOLON) advance();
    return node;
}

ASTNode* parse() {
    advance(); 
    ASTNode* head = NULL;
    ASTNode* current = NULL;
    while (parser.current.type != TOKEN_EOF) {
        ASTNode* stmt = statement();
        if (head == NULL) head = stmt;
        else current->next = stmt;
        current = stmt;
    }
    return head;
}