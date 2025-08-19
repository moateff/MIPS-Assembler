#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "encode.h"
#include "utils.h"
#include "labeltab.h"
#include "config.h"
#include "assembler.h"


void assembler_init(AssemblerContext *ctx) {
    if (!ctx) return;

    ctx->inputFile = NULL;
    ctx->outputFile = NULL;
    initLabelTab(&ctx->labels); 
}


void assembler_free(AssemblerContext *ctx) {
    if (!ctx) return;

    if (ctx->inputFile) {
        fclose(ctx->inputFile);
        ctx->inputFile = NULL;
    }

    if (ctx->outputFile) {
        fclose(ctx->outputFile);
        ctx->outputFile = NULL;
    }

    initLabelTab(&ctx->labels);
}

// First pass: build label table
void assembler_run_pass1(AssemblerContext *ctx) {
    char line[MAX_LINE_LEN];
    int address = 0;

    while (fgets(line, sizeof(line), ctx->inputFile)) {
        preprocessLine(line); 

        if (strlen(line) <= 2) continue; // skip empty lines

        char label[MAX_LABEL_LEN];

        if (tokenizeLabel(line, label)) { // if label exists
            if (!addLabel(&(ctx->labels), label, address)) {
                fprintf(stderr, "Duplicate label: %s\n", label);
            }
        }

        if (lineHasInstruction(line)) {
            address += 4; // assume each instruction = 4 bytes
        }
    }
}

// Second pass: generate machine code
void assembler_run_pass2(AssemblerContext *ctx){
    char line[MAX_LINE_LEN];
    int address = 0; // instruction address counter

    while (fgets(line, sizeof(line), ctx->inputFile)) {
        preprocessLine(line); 
        
        if (strlen(line) <= 2) continue; // skip empty lines
        
        ParsedInstruction Instr;

        int count = parseLine(line, &Instr, &(ctx->labels));
        if (count == 0) continue;
        Instr.address = address; // set instruction address

        uint32_t machineCode = encodeInstruction(&Instr, &(ctx->labels));
        fprintf(ctx->outputFile, "%08X\n", machineCode); 
        address += 4; 
    }
}

/*
assembler.c: In function ‘assembler_run_pass1’:
assembler.c:46:24: warning: multi-character character constant [-Wmultichar]
   46 |         if (line[0] == '/n') continue; // skip empty lines
      |                        ^~~~
*/