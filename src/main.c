#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "labeltab.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <input.asm> [output.hex]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFileName = argv[1];
    char outputFileName[MAX_FILENAME_LEN];  // enough space for path

    if (argc == 3) {
        strncpy(outputFileName, argv[2], sizeof(outputFileName));
        outputFileName[sizeof(outputFileName) - 1] = '\0'; // ensure null-termination
    } else {
        // derive from input
        strncpy(outputFileName, inputFileName, sizeof(outputFileName));
        outputFileName[sizeof(outputFileName) - 1] = '\0';

        char *dot = strrchr(outputFileName, '.');
        if (dot != NULL) {
            *dot = '\0';  // remove extension
        }
        strncat(outputFileName, ".hex", sizeof(outputFileName) - strlen(outputFileName) - 1);
    }

    AssemblerContext ctx;
    assembler_init(&ctx);

    ctx.inputFile = fopen(inputFileName, "r");
    if (!ctx.inputFile) {
        perror("Error opening input file");
        assembler_free(&ctx);
        return EXIT_FAILURE;
    }

    ctx.outputFile = fopen(outputFileName, "wb");
    if (!ctx.outputFile) {
        perror("Error opening output file");
        fclose(ctx.inputFile);
        assembler_free(&ctx);
        return EXIT_FAILURE;
    }

    assembler_run_pass1(&ctx); 
    rewind(ctx.inputFile); 
    assembler_run_pass2(&ctx); 
    assembler_free(&ctx);

    return EXIT_SUCCESS;
}
