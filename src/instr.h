#ifndef INSTR_H
#define INSTR_H

typedef enum {
    R_TYPE,
    I_TYPE,
    J_TYPE
} InstType;

typedef struct {
    char *mnemonic;    
    InstType type;    
    int opcode;     
    int funct;        // for R-type only
} Instruction;

typedef struct {
    const char *name;
    int number;
} RegisterMap;

extern const Instruction instructionSet[];
extern const RegisterMap regTable[];

// Function prototypes
const Instruction* findInstruction(const char *mnemonic);
int getRegisterNumber(const char *reg);
const char* getRegisterName(int regNum);

#endif // INSTR_H
