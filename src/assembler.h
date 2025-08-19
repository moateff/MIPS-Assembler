#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include "labeltab.h"

typedef struct {
    FILE *inputFile;
    FILE *outputFile;
    LabelTab labels;
} AssemblerContext;

void assembler_init(AssemblerContext *ctx);
void assembler_run_pass1(AssemblerContext *ctx);
void assembler_run_pass2(AssemblerContext *ctx);
void assembler_free(AssemblerContext *ctx);

#endif // ASSEMBLER_H
