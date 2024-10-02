#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX_TOKENS 10

#define R_type 1
#define I_type 2
#define J_type 3

int get_line(char *ptr){
    int ch, n = 0;
    while ((ch = getchar()) != '\n'){
        *(ptr++) = (char)ch;
        n++;
    }
    *ptr = '\0';
    return n;
}

int read_input(char *input){
    int count = 0;
    printf("\nEnter Assembly Instruction : ");
    return count = get_line(input);
}

bool check_reg (char *str){
    return !strcmp(str,"$zero")|| !strcmp(str,"$at") || !strcmp(str,"$v0") || !strcmp(str,"$v1") ||
            !strcmp(str,"$a0") || !strcmp(str,"$a1") || !strcmp(str,"$a3") || !strcmp(str,"$a3") || 
            !strcmp(str,"$t0") || !strcmp(str,"$t1") || !strcmp(str,"$t2") || !strcmp(str,"$t3") || 
            !strcmp(str,"$t4") || !strcmp(str,"$t5") || !strcmp(str,"$t6") || !strcmp(str,"$t7") || 
            !strcmp(str,"$t8") || !strcmp(str,"$t9") || !strcmp(str,"$s0") || !strcmp(str,"$s1") || 
            !strcmp(str,"$s2") || !strcmp(str,"$s3") || !strcmp(str,"$s4") || !strcmp(str,"$s5") || 
            !strcmp(str,"$s6") || !strcmp(str,"$s7") || !strcmp(str,"$k0") || !strcmp(str,"$k1") || 
            !strcmp(str,"$gp") || !strcmp(str,"$sp") || !strcmp(str,"$fp") || !strcmp(str,"$ra");
}

bool check_validation(char *tokens[], int n, int type){
    if(type == R_type){
        if(n != 4) return false;
        for (int i = 1; i < n; i++)
            if(!check_reg(tokens[i])) return false; 
        return true; 
    }
    else if(type == I_type){
        if(n != 4) return false;
        for (int i = 1; i < n - 1; i++)
            if (!check_reg(tokens[i])) return false;
        return true; 
    }
    else if(type == J_type){
        if(n != 2) return false;
        return true;
    }
    return false;
}

int check_type(char *str){
    if(!strcmp(str,"ADD") || !strcmp(str,"SUB") || !strcmp(str,"AND") || !strcmp(str,"OR") ||
            !strcmp(str,"MUL") || !strcmp(str,"DIV") || !strcmp(str,"SLT") || !strcmp(str,"JR") ||
            !strcmp(str,"SRL") || !strcmp(str,"SLL"))
        return R_type;
    else if(!strcmp(str,"LW") || !strcmp(str,"SW") || !strcmp(str,"BEQ") || !strcmp(str,"BNE") ||
            !strcmp(str,"ADDI") || !strcmp(str,"ANDI") || !strcmp(str,"ORI") || !strcmp(str,"SLTI") ||
            !strcmp(str,"LUI"))
        return I_type;
    else if(!strcmp(str,"J") || !strcmp(str,"JAL"))
        return J_type;
    else
        return 0;
}

int parse(char *input, char **tokens){
    int count = 0;
    char *token = strtok(input, " ");
    while (token != NULL && count < MAX_TOKENS-1){
        
        *tokens++ = token;
        count++;
        token = strtok(NULL, " ");
    }  
    *tokens = '\0';
    return  count;
}

int opcode_decoder(char *str, int type){
    if(type == R_type) return 0;
    else if(type == I_type){
        if(!strcmp(str, "LW")) return 0b100011;
        else if(!strcmp(str, "SW")) return 0b101011;
        else if(!strcmp(str, "BEQ")) return 0b000100;
        else if(!strcmp(str, "BNE")) return 0b000101;
        else if(!strcmp(str, "ADDI")) return 0b001000;
        else if(!strcmp(str, "ANDI")) return 0b001100;
        else if(!strcmp(str, "ORI")) return 0b001101;
        else if(!strcmp(str, "SLTI")) return 0b001010;
        else if(!strcmp(str, "LUI")) return 0b001111;
        else return 0;
    }
    else if(type == J_type){
        if(!strcmp(str, "J")) return 0b000010;
        else if(!strcmp(str, "JAL")) return 0b000011;
        else return 0;
    }
    else return 0;
}

int funct_decoder(char *str){
    if(!strcmp(str,"ADD"))  return 0b100000;
    else if(!strcmp(str,"SUB")) return 0b100010;
    else if(!strcmp(str,"AND")) return 0b100100;
    else if(!strcmp(str,"OR")) return 0b100101;
    else if(!strcmp(str,"SLT")) return 0b101010;
    else if(!strcmp(str,"SLL")) return 0b000000;
    else if(!strcmp(str,"SRL")) return 0b000010;
    else if(!strcmp(str,"JR")) return 0b001000;
    else if(!strcmp(str,"MUL")) return 0b011000;
    else if(!strcmp(str,"DIV")) return 0b011010;
    else return 1;
}

int reg_decoder(char *str){
    if(!strcmp(str,"$zero")) return 0;
    else if(!strcmp(str,"$at")) return 1;
    else if(!strcmp(str,"$v0")) return 2;
    else if(!strcmp(str,"$v1")) return 3;
    else if(!strcmp(str,"$a0")) return 4;
    else if(!strcmp(str,"$a1")) return 5;
    else if(!strcmp(str,"$a2")) return 6;
    else if(!strcmp(str,"$a3")) return 7;
    else if(!strcmp(str,"$t0")) return 8;
    else if(!strcmp(str,"$t1")) return 9;
    else if(!strcmp(str,"$t2")) return 10;
    else if(!strcmp(str,"$t3")) return 11;
    else if(!strcmp(str,"$t4")) return 12; 
    else if(!strcmp(str,"$t5")) return 13;
    else if(!strcmp(str,"$t6")) return 14;
    else if(!strcmp(str,"$t7")) return 15;
    else if(!strcmp(str,"$t8")) return 24;
    else if(!strcmp(str,"$t9")) return 25;
    else if(!strcmp(str,"$s0")) return 16;
    else if(!strcmp(str,"$s1")) return 17;
    else if(!strcmp(str,"$s2")) return 18;
    else if(!strcmp(str,"$s3")) return 19;
    else if(!strcmp(str,"$s4")) return 20;
    else if(!strcmp(str,"$s5")) return 21; 
    else if(!strcmp(str,"$s6")) return 22;
    else if(!strcmp(str,"$s7")) return 23;
    else if(!strcmp(str,"$k0")) return 26;
    else if(!strcmp(str,"$k1")) return 27;
    else if(!strcmp(str,"$gp")) return 28;
    else if(!strcmp(str,"$sp")) return 29;
    else if(!strcmp(str,"$fp")) return 30;
    else if(!strcmp(str,"$ra")) return 31;
    else return 32;
    
}

void print_binary(int num, int precision){
    for (int i = precision - 1; i >= 0; i--){   // Start from the highest bit of the precision down to 0
        unsigned int mask = 1u << i;
        printf("%c", (num & mask) ? '1' : '0'); // Print 1 if the bit is set, 0 otherwise
    }
    printf(" ");
}

void print_R_type(int opcode, int rs, int rt, int rd, int shamt, int funct){
    printf("\nInstruction Type           : R type\n");
    printf("Binary Representation      : ");
    print_binary(opcode, 6);
    print_binary(rs, 5);
    print_binary(rt, 5);
    print_binary(rd, 5);
    print_binary(shamt, 5);
    print_binary(funct, 6);
    printf("\n");
}

int hex_R_type(int opcode, int rs, int rt, int rd, int shamt, int funct){
    return (funct | (shamt << 6) | (rd << 11) | (rt << 16) | (rs << 21) | (opcode << 26));
}

void print_I_type(int opcode, int rs, int rt, int immediate){
    printf("\nInstruction Type           : I type\n");
    printf("Binary Representation      : ");
    print_binary(opcode, 6);
    print_binary(rs, 5);
    print_binary(rt, 5);
    print_binary(immediate, 16);
    printf("\n");
}

int hex_I_type(int opcode, int rs, int rt, int immediate){
    return ((immediate & 0xffff) | (rt << 16) | (rs << 21) | (opcode << 26));
}

void print_J_type(int opcode, int address){
    printf("\nInstruction Type           : J type\n");
    printf("Binary Representation      : ");
    print_binary(opcode, 6);
    print_binary(address, 26);
    printf("\n");
}

int hex_J_type(int opcode, int address){
    return ((address & 0x3ffffff) | (opcode << 26));
}

int decoder(char *tokens[], int n, int type){
    if(type == R_type){
        int opcode = opcode_decoder(tokens[0], type);
        int rs = reg_decoder(tokens[2]);
        int rt = reg_decoder(tokens[3]);
        int rd = reg_decoder(tokens[1]);
        int shamt = 0;
        int funct = funct_decoder(tokens[0]);
        print_R_type(opcode, rs, rt, rd, shamt, funct);
        return hex_R_type(opcode, rs, rt, rd, shamt, funct);
    }
    else if(type == I_type){
        int opcode = opcode_decoder(tokens[0], type);
        int rs = reg_decoder(tokens[2]);
        int rt = reg_decoder(tokens[1]);
        int immediate = atoi(tokens[3]);  // Convert string to int
        print_I_type(opcode, rs, rt, immediate);
        return hex_I_type(opcode, rs, rt, immediate);
    }
    else if(type == J_type){
        int opcode = opcode_decoder(tokens[0], type);
        int address = atoi(tokens[1]);    // Convert string to int
        print_J_type(opcode, address);
        return hex_J_type(opcode, address);
    }
    return 0;
}

void fun(){
    printf("\nIn MIPS assembly, instructions are classified into three main types: R-type, I-type, and J-type. Each type has its own \n");
    printf("specific format in terms of how the instruction is encoded in a 32-bit binary representation.\n");
    printf("\n1. R-Type Instruction Format:\n");
    printf("31     26     21    16    11     6        0\n");
    printf("+-------+------+-----+-----+------+-------+\n");
    printf("|opcode | rs   | rt  | rd  |shamt | funct |\n");
    printf("+-------+------+-----+-----+------+-------+\n");
    printf("\n2. I-Type Instruction Format\n");
    printf("31     26     21    16                    0\n");
    printf("+-------+------+-----+--------------------+\n");
    printf("|opcode | rs   | rt  |     immediate      |\n");
    printf("+-------+------+-----+--------------------+\n");
    printf("\n3. J-Type Instruction Format\n");
    printf("31     26                                 0\n");
    printf("+-------+---------------------------------+\n");
    printf("|opcode |        target address           |\n");
    printf("+-------+---------------------------------+\n");
    printf("");
}

int main(){
    char input[MAX_LENGTH];
    char *args[MAX_TOKENS];
    int number_of_args, instruction_type, hex;
    fun();
    while (true)
    {
        read_input(input);
        number_of_args = parse(input, args);
        instruction_type = check_type(args[0]);
        if(!check_validation(args, number_of_args, instruction_type))
            printf("\nInvalid ASSEMBLY INSTRUCTION\n");
        else{
            hex = decoder(args, number_of_args, instruction_type);
            printf("Hex Representation         : 0x%08x\n", hex);
        }
    }
    return 0;
}
/*
ADD $s0 $t0 $t1
AND $s0 $t0 $t1
SUB $s0 $t0 $t1 
SLT $s0 $t0 $t1
OR $s0 $t0 $t1
MUL $s0 $t0 $t1
LW $s0 $t0 4
SW $s0 $t0 4
BEQ $s0 $s1 8
BNE $s0 $s1 8
ADDI $s0 $t0 10
ANDI $s0 $t0 15
ORI $s0 $t0 5
J 1000
JAL 2000
SUB $s0 $t4 $zero
*/