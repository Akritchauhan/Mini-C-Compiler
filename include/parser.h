#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "ast.h"

typedef struct {
    Token current;
    Token previous;
    int hadError;
} Parser;

void initParser();
ASTNode* parse();

#endif