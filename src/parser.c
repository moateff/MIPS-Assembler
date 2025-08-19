#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "utils.h"
#include "instr.h"
#include "labeltab.h"

// Tokenize a line into an array of tokens
// Returns number of tokens found, up to maxTokens
int tokenizeLine(char *line, char *tokens[], int maxTokens) {
    int count = 0;
    char *token = strtok(line, " :(),\t");
    while (token != NULL && count < maxTokens) {
        tokens[count++] = token;
        token = strtok(NULL, " :(),\t");
    }
    return count;
}

int tokenizeLabel(const char *line, char *label) {
    const char *colon = strchr(line, ':');
    if (colon) {
        int len = colon - line;
        strncpy(label, line, len);
        label[len] = '\0';
        trimSpaces(label); // remove spaces around label
        return 1; // label found
    } else {
        label[0] = '\0'; 
        return 0; // no label found
    }
}

// Returns 1 if mnemonic is valid and fills outInstr
// Returns 0 if invalid mnemonic
int parseInstruction(const char *mnemonic, Instruction *outInstr) {
    const Instruction *instr = findInstruction(mnemonic);
    if (instr) {
        if (outInstr) {
            memcpy(outInstr, instr, sizeof(Instruction));
        }
        return 1; 
    }
    return 0; // invalid mnemonic
}

// Returns -1 if invalid register, otherwise returns register number
int parseRegister(const char *token) {
    return getRegisterNumber(token); 
}

// Parses an immedi/ successate value from a token
int parseImmediate(const char *token, int *value) {
    if (!token || !value) return 0;

    char *endptr;
    if (token[0] == '0' && token[1] == 'x') {
        *value = (int)strtol(token, &endptr, 16); // hex
    } else {
        *value = (int)strtol(token, &endptr, 10); // decimal
    }

    return (*endptr == '\0'); // returns 1 if fully valid
}

// Parses a label from a token
// Returns -1 if label not found, otherwise returns address
int parseLabel(const char *token, const LabelTab *labels) {
    int addr = lookupLabel(labels, token);
    return addr;
}

// Full line parsing
int parseLine(char *line, ParsedInstruction *outInstr, const LabelTab *labels) {
    if (!line || !outInstr) return 0;

    char *tokens[MAX_TOKENS];
    int numTokens = tokenizeLine(line, tokens, MAX_TOKENS);
    if (numTokens == 0) return 0;

    int tokenIdx = 0;

    // Check for label
    if (parseInstruction(tokens[tokenIdx], NULL) == 0) {
        // assume label
        if (parseLabel(tokens[tokenIdx], labels) != -1) {
            tokenIdx++; // skip label
            if (tokenIdx >= numTokens) return 0;
        }
    }

    // Parse instruction
    if (!parseInstruction(tokens[tokenIdx], &outInstr->instr)) {
        printf("Error: Unknown instruction '%s'\n", tokens[tokenIdx]);
        return 0;
    }

    Instruction *instr = &outInstr->instr;
    tokenIdx++;

    // Reset operand fields
    outInstr->rd = outInstr->rs = outInstr->rt = -1;
    outInstr->immediate = 0;
    outInstr->label[0] = '\0';

    // Parse operands based on type
    if (instr->type == R_TYPE) {
        if (tokenIdx + 2 >= numTokens) return 0;
        outInstr->rd = parseRegister(tokens[tokenIdx++]);
        outInstr->rs = parseRegister(tokens[tokenIdx++]);
        outInstr->rt = parseRegister(tokens[tokenIdx++]);
    }
    else if (instr->type == I_TYPE) {
        if (strcmp(instr->mnemonic, "lw") == 0 || strcmp(instr->mnemonic, "sw") == 0) {
            // format: rt, offset(rs)
            outInstr->rt = parseRegister(tokens[tokenIdx++]);
            if (!parseImmediate(tokens[tokenIdx++], &outInstr->immediate)) return 0;
            outInstr->rs = parseRegister(tokens[tokenIdx++]);
        } else if (strcmp(instr->mnemonic, "beq") == 0) {
            // format: rs, rt, label
            outInstr->rs = parseRegister(tokens[tokenIdx++]);
            outInstr->rt = parseRegister(tokens[tokenIdx++]);
            strncpy(outInstr->label, tokens[tokenIdx++], sizeof(outInstr->label)-1);
            outInstr->label[sizeof(outInstr->label)-1] = '\0';
        } else { // addi, andi, ori
            // format: rt, rs, imm
            outInstr->rt = parseRegister(tokens[tokenIdx++]);
            outInstr->rs = parseRegister(tokens[tokenIdx++]);
            if (!parseImmediate(tokens[tokenIdx++], &outInstr->immediate)) return 0;
        }
    }
    else if (instr->type == J_TYPE) {
        if (tokenIdx >= numTokens) return 0;
        strncpy(outInstr->label, tokens[tokenIdx++], sizeof(outInstr->label)-1);
        outInstr->label[sizeof(outInstr->label)-1] = '\0';
    }

    return 1; // success
}

void printParsedInstruction(const ParsedInstruction *pi) {
    if (!pi) return;

    printf("Instruction: %s\n", pi->instr.mnemonic);
    printf("  Type: %s\n",
        (pi->instr.type == R_TYPE) ? "R" :
        (pi->instr.type == I_TYPE) ? "I" :
        "J");

    if (pi->instr.type == R_TYPE) {
        printf("  rd: %s ($%d)\n", getRegisterName(pi->rd), pi->rd);
        printf("  rs: %s ($%d)\n", getRegisterName(pi->rs), pi->rs);
        printf("  rt: %s ($%d)\n", getRegisterName(pi->rt), pi->rt);
    } 
    else if (pi->instr.type == I_TYPE) {
        printf("  rt: %s ($%d)\n", getRegisterName(pi->rt), pi->rt);
        printf("  rs: %s ($%d)\n", getRegisterName(pi->rs), pi->rs);
        printf("  immediate: %d\n", pi->immediate);
        if (pi->label[0] != '\0') {
            printf("  label: %s\n", pi->label);
        }
    } 
    else if (pi->instr.type == J_TYPE) {
        printf("  label: %s\n", pi->label);
    }
    printf("\n");
}