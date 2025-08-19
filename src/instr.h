#ifndef INSTR_H
#define INSTR_H

// Instruction types
typedef enum {
    R_TYPE,
    I_TYPE,
    J_TYPE
} InstType;

// Instruction structure
typedef struct {
    char *mnemonic;    
    InstType type;    
    int opcode;     
    int funct;        // for R-type only
} Instruction;

// Register structure
typedef struct {
    const char *name;
    int number;
} RegisterMap;

// Table of instructions and registers
extern const Instruction instructionSet[];
extern const RegisterMap regTable[];

// Function prototypes
const Instruction* findInstruction(const char *mnemonic);
void printInstruction(const char *mnemonic);

int getRegisterNumber(const char *reg);
void printRegister(const char *reg);
const char* getRegisterName(int regNum);

#endif // INSTR_H
