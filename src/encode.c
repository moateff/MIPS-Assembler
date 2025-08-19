#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "encode.h"

// sign-extend immediate to 16 bits
static uint16_t encodeImmediate(int value) {
    return (uint16_t)(value & 0xFFFF);
}

// resolve label offset for branches (relative)
int resolveLabelOffset(const char *label, int currentAddr, const LabelTab *labels) {
    if (!label || !labels) return 0;
    int target = lookupLabel(labels, label);
    if (target == -1) {
        printf("Error: Undefined label '%s'\n", label);
        return 0;
    }

    return (target - (currentAddr + 4)) / 4;
}

// Main encoder
uint32_t encodeInstruction(const ParsedInstruction *pi, const LabelTab *labels) {
    if (!pi) return 0;

    uint32_t word = 0;
    const Instruction *instr = &pi->instr;

    switch (instr->type) {
        case R_TYPE:
            word |= (instr->opcode & 0x3F) << 26;        // opcode
            word |= (pi->rs & 0x1F) << 21;               // rs
            word |= (pi->rt & 0x1F) << 16;               // rt
            word |= (pi->rd & 0x1F) << 11;               // rd
            word |= 0 << 6;                              // shamt = 0
            word |= (instr->funct & 0x3F);               // funct
            break;

        case I_TYPE:
            word |= (instr->opcode & 0x3F) << 26;
            if (strcmp(instr->mnemonic, "lw") == 0 || strcmp(instr->mnemonic, "sw") == 0) {
                word |= (pi->rs & 0x1F) << 21;           // rs
                word |= (pi->rt & 0x1F) << 16;           // rt
                word |= encodeImmediate(pi->immediate);  // immediate
            } else if (strcmp(instr->mnemonic, "beq") == 0) {
                word |= (pi->rs & 0x1F) << 21;           // rs
                word |= (pi->rt & 0x1F) << 16;           // rt   
                int offset = resolveLabelOffset(pi->label, pi->address, labels);            
                word |= encodeImmediate(offset);         // immediate
            } else { // addi, andi, ori
                word |= (pi->rs & 0x1F) << 21;           // rs
                word |= (pi->rt & 0x1F) << 16;           // rt
                word |= encodeImmediate(pi->immediate);  // immediate                  
            }
            break;

        case J_TYPE:
            word |= (instr->opcode & 0x3F) << 26;
            {
                int addr = lookupLabel(labels, pi->label);
                if (addr == -1) {
                    printf("Error: Undefined label '%s'\n", pi->label);
                    addr = 0;
                }
                word |= (addr >> 2) & 0x03FFFFFF;        // address
            }
            break;
    }

    return word;
}
