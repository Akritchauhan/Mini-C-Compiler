#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static Token number() {
    while (isdigit(peek())) advance();
    return makeToken(TOKEN_NUMBER);
}

static Token identifier() {
    while (isalnum(peek()) || peek() == '_') advance();
    int length = (int)(scanner.current - scanner.start);
    if (length == 5 && memcmp(scanner.start, "print", 5) == 0) return makeToken(TOKEN_PRINT);
    if (length == 3 && memcmp(scanner.start, "int", 3) == 0) return makeToken(TOKEN_INT);
    return makeToken(TOKEN_IDENTIFIER);
}

Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;
    if (isAtEnd()) return makeToken(TOKEN_EOF);
    char c = advance();
    if (isdigit(c)) return number();
    if (isalpha(c) || c == '_') return identifier();
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
