#ifndef PARSER_H
#define PARSER_H

#include "instr.h"
#include "labeltab.h"
#include "config.h"

typedef struct {
    Instruction instr;  // mnemonic info
    int address;        // instruction address in memory
    int rd;             // destination register (R/I)
    int rs;             // source register (R/I)
    int rt;             // target register (R/I)
    int immediate;      // immediate value (I-type)
    char label[MAX_LABEL_LEN];     // label for branch/jump
} ParsedInstruction;

// Tokenization
int tokenizeLine(char *line, char *tokens[], int maxTokens); 
int tokenizeLabel(const char *line, char *label);

// Instruction Parsing
int parseInstruction(const char *mnemonic, Instruction *outInstr);

// Operand Parsing
int parseRegister(const char *token);
int parseImmediate(const char *token, int *value);
int parseLabel(const char *token, const LabelTab *labels);

// High-Level Orchestrator
int parseLine(char *line, ParsedInstruction *outInstr, const LabelTab *labels);

// For debugging
void printParsedInstruction(const ParsedInstruction *pi);

#endif // PARSER_H
