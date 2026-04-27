#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "scanner.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: minicc <source_file>\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    fread(buffer, sizeof(char), fileSize, file);
    buffer[fileSize] = '\0';

    initScanner(buffer);

    printf("Source Code:\n%s\n", buffer);

    fclose(file);
    free(buffer);
    return 0;
}