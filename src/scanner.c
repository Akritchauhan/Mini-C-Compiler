#include <string.h>
#include "scanner.h"
#include <ctype.h>
#include "tokens.h"

extern Scanner scanner;


static int isDigit(char c) {
    return c >= '0' && c <= '9';
}

static int isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}


static int isAtEnd() {
    return *scanner.current == '\0';
}

static char peek() {
    return *scanner.current;
}


static char advance() {
    scanner.current++;
    return scanner.current[-1];
}


static void skipWhitespace() {
    while (*scanner.current == ' ' || *scanner.current == '\t' || *scanner.current == '\n') {
        if (*scanner.current == '\n') scanner.line++;
        scanner.current++;
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
    while (isDigit(peek())) advance();
    return makeToken(TOKEN_NUMBER);
}


static TokenType identifierType() {
    int length = (int)(scanner.current - scanner.start);
    
    // Simple check for "print" keyword
    if (length == 5 && memcmp(scanner.start, "print", 5) == 0) {
        return TOKEN_PRINT;
    }
    // Simple check for "int" keyword
    if (length == 3 && memcmp(scanner.start, "int", 3) == 0) {
        return TOKEN_INT;
    }

    return TOKEN_IDENTIFIER;
}

// Scan identifier or keyword
static Token identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}

Token scanToken() {
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    // Check for identifiers/keywords
    if (isAlpha(c)) return identifier();

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