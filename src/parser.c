#include <stdio.h>
#include "parser.h"

Parser parser;

static void advanceParser() {
    parser.previous = parser.current;

    for (;;) {
        parser.current = scanToken();
        if (parser.current.type != TOKEN_ERROR) break;

        fprintf(stderr, "Lexical Error at line %d: %.*s\n", 
                parser.current.line, parser.current.length, parser.current.start);
        parser.hadError = 1;
    }
}

static void consume(TokenType type, const char* message) {
    if (parser.current.type == type) {
        advanceParser();
        return;
    }

    fprintf(stderr, "Parser Error at line %d: %s\n", parser.current.line, message);
    parser.hadError = 1;
}

void initParser() {
    parser.hadError = 0;
    advanceParser();
}

ASTNode* parse() {
    initParser();
    // Logic for expression parsing will be added on Day 13
    return NULL;
}