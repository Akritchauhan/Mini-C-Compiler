#include <string.h>
#include "scanner.h"
#include <ctype.h>

extern Scanner scanner;

// Helper to check for digits
static int isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Helper to check if at end of input
static int isAtEnd() {
    return *scanner.current == '\0';
}

// Helper to peek at current character without advancing
static char peek() {
    return *scanner.current;
}

// Helper to advance and return current character
static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

// Helper to skip whitespace characters
static void skipWhitespace() {
    while (*scanner.current == ' ' || *scanner.current == '\t' || *scanner.current == '\n') {
        if (*scanner.current == '\n') scanner.line++;
        scanner.current++;
    }
}

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

// Consumes all consecutive digits
static Token number() {
    while (isDigit(peek())) advance();
    return makeToken(TOKEN_NUMBER);
}

Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    // Check for numbers
    if (isDigit(c)) return number();

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