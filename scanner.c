#include <stdio.h>
#include "scanner.h"

Scanner scanner;

void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

static int isAtEnd() {
    return *scanner.current == '\0';
}

static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

static char peek() {
    return *scanner.current;
}

static void skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            default:
                return;
        }
    }
}

// Basic scanToken to satisfy the compiler for now
Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) {
        Token token = {TOKEN_EOF, scanner.current, 0, scanner.line};
        return token;
    }

    // Day 5 will fill this switch case
    return (Token){TOKEN_ERROR, scanner.current, 0, scanner.line};
}