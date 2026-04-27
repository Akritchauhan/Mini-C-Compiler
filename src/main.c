#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;
    FILE* f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    char* buf = malloc(size + 1);
    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);

    initScanner(buf);
    ASTNode* root = parse();
    
    printf(".intel_syntax noprefix\n.global main\nmain:\n");
    gen(root);
    printf("  ret\n");

    return 0;
}