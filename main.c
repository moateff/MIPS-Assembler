#include <stdio.h>
#include <stdlib.h>
#include "assembler.h"
#include "labeltab.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.asm> <output.hex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    AssemblerContext ctx;
    assembler_init(&ctx);

    ctx.inFile = fopen(argv[1], "r");
    if (!ctx.inFile) {
        perror("Error opening input file");
        assembler_free(&ctx);
        return EXIT_FAILURE;
    }

    ctx.outFile = fopen(argv[2], "wb");
    if (!ctx.outFile) {
        perror("Error opening output file");
        fclose(ctx.inFile);
        assembler_free(&ctx);
        return EXIT_FAILURE;
    }

    assembler_run_pass1(&ctx);  // Pass 1: build label table
    dumpLabelTable(&ctx.labels); 
    rewind(ctx.inFile); 
    assembler_run_pass2(&ctx);  // Pass 2: generate machine code
    assembler_free(&ctx);

    return EXIT_SUCCESS;
}
