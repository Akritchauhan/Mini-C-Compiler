#ifndef SCANNER_H
#define SCANNER_H

#include "tokens.h"

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

void initScanner(const char* source);

#endif