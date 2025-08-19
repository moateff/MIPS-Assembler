#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "instr.h"
#include "utils.h"

// Define the instruction set
const Instruction instructionSet[] = {
    {"add",  R_TYPE, 0x00, 0x20}, // opcode=0, funct=32
    {"sub",  R_TYPE, 0x00, 0x22},
    {"and",  R_TYPE, 0x00, 0x24},
    {"or",   R_TYPE, 0x00, 0x25},
    {"slt",  R_TYPE, 0x00, 0x2A},
    {"addi", I_TYPE, 0x08, -1}, // funct unused
    {"lw",   I_TYPE, 0x23, -1},
    {"sw",   I_TYPE, 0x2B, -1},
    {"beq",  I_TYPE, 0x04, -1},
    {"j",    J_TYPE, 0x02, -1}, 
    {NULL, 0, 0, 0} // sentinel (end marker)
};

// Define the register map
const RegisterMap regTable[] = {
    {"$zero", 0}, {"$at", 1},
    {"$v0", 2}, {"$v1", 3},
    {"$a0", 4}, {"$a1", 5}, {"$a2", 6}, {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11},
    {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19},
    {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25},
    {"$k0", 26}, {"$k1", 27},
    {"$gp", 28}, {"$sp", 29}, {"$fp", 30}, {"$ra", 31},
    {NULL, -1} // sentinel (end marker)
};

const Instruction* findInstruction(const char *mnemonic) {
    for (int i = 0; instructionSet[i].mnemonic != NULL; i++) {
        if (my_strcasecmp(instructionSet[i].mnemonic, mnemonic) == 0) { // case-insensitive comparison
            return &instructionSet[i];
        }
    }
    return NULL; // not found
}

void printInstruction(const char *mnemonic) {
    const Instruction *instr = findInstruction(mnemonic);
    if (instr) {
        printf("Mnemonic: %s, Type: %d, Opcode: 0x%02X, Funct: 0x%02X\n",
               instr->mnemonic, instr->type, instr->opcode, instr->funct);
    } else {
        printf("Error: Unknown instruction '%s'\n", mnemonic);
    }
}

int getRegisterNumber(const char *reg) {
    // First: check if it matches a name
    for (size_t i = 0; regTable[i].name != NULL; i++) {
        if (my_strcasecmp(reg, regTable[i].name) == 0) { // case-insensitive comparison
            return regTable[i].number;
        }
    }

    // Second: check if it is numeric like $8 or $31
    if (reg[0] == '$' && isdigit((unsigned char)reg[1])) {
        int num = atoi(reg + 1); // skip '$'
        if (num >= 0 && num < 32) {
            return num;
        }
    }

    // Invalid register
    return -1;
}

// Returns the register name for a given number, or NULL if not found
const char* getRegisterName(int regNum) {
    for (int i = 0; regTable[i].name != NULL; i++) {
        if (regTable[i].number == regNum) {
            return regTable[i].name;
        }
    }
    return NULL; // unknown register
}

void printRegister(const char *reg) {
    int num = getRegisterNumber(reg);
    if (num != -1) {
        printf("Register: %s -> $%d\n", reg, num);
    } else {
        printf("Error: Unknown register '%s'\n", reg);
    }
}