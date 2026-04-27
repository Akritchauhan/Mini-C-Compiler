#include <string.h>
#include "scanner.h"

extern Scanner scanner;

// Helper to package a token
static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

// Helper for error tokens
static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    switch (c) {
        case '+': return makeToken(TOKEN_PLUS);
        case '-': return makeToken(TOKEN_MINUS);
        case '*': return makeToken(TOKEN_STAR);
        case '/': return makeToken(TOKEN_SLASH);
        case '=': return makeToken(TOKEN_EQUAL);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case '(': return makeToken(TOKEN_LPAREN);
        case ')': return makeToken(TOKEN_RPAREN);
    }

    return errorToken("Unexpected character.");
}