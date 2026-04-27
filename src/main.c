#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "parser.h"
#include "ast.h"

static void run(const char* source) {
    initScanner(source);
    ASTNode* root = parse();
    
    if (root != NULL) {
        printf("Parsed successfully: %.*s\n", root->token.length, root->token.start);
    }
}

static void runFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);
    run(buffer);
    free(buffer);
}

static void runPrompt() {
    char line[1024];
    printf("MiniC REPL - Type 'exit' to quit\n");
    for (;;) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin) || strcmp(line, "exit\n") == 0) break;
        run(line);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        runPrompt();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: minicc [path]\n");
        return 64;
    }
    return 0;
}