#include <stdlib.h>
#include "parser.h"

extern Parser parser;

static ASTNode* primary() {
    if (parser.previous.type == TOKEN_NUMBER) {
        return createNode(NODE_LITERAL, parser.previous);
    }

    if (parser.previous.type == TOKEN_IDENTIFIER) {
        return createNode(NODE_VARIABLE, parser.previous);
    }

    if (parser.previous.type == TOKEN_LPAREN) {
        ASTNode* node = parse(); // Recursive call for nested expressions
        consume(TOKEN_RPAREN, "Expect ')' after expression.");
        return node;
    }

    return NULL; 
}

ASTNode* parse() {
    initParser();
    advanceParser(); // Prime the pump
    return primary();
}