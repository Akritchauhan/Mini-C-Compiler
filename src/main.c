#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "tokens.h"

void printToken(Token token) {
    const char* typeNames[] = {
        "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_STAR", "TOKEN_SLASH",
        "TOKEN_EQUAL", "TOKEN_SEMICOLON", "TOKEN_LPAREN", "TOKEN_RPAREN",
        "TOKEN_NUMBER", "TOKEN_IDENTIFIER", "TOKEN_INT", "TOKEN_PRINT",
        "TOKEN_EOF", "TOKEN_ERROR"
    };

    printf("%02d | %-16s | '%.*s'\n", 
           token.line, typeNames[token.type], token.length, token.start);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: minicc <source_file>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) return 1;
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char* buffer = (char*)malloc(fileSize + 1);
    fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    initScanner(buffer);

    printf("LINE | TYPE             | CONTENT\n");
    printf("----------------------------------\n");

    for (;;) {
        Token token = scanToken();
        printToken(token);
        if (token.type == TOKEN_EOF) break;
    }

    free(buffer);
    return 0;
}