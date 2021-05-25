#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>
#include <stdbool.h>

// TYPE DECLARATIONS:
// type definitions for readability
typedef uint32_t word;
typedef uint32_t instruction;
typedef uint16_t location;
typedef uint8_t byte;

// 64KB memory (16 bit address)
#define MEMSIZE (1 << 16)

// maximum word (all 1s)
#define MAXINT32 0xFFFFFFFF

// Hold the state of the emulator
//CPSR = NZCV

typedef struct {
    unsigned int N : 1;
    unsigned int Z : 1;
    unsigned int C : 1;
    unsigned int V : 1;
} cpsr;

typedef struct {
    word registers[16];
    cpsr CPSR;
    byte *memory; 
} machineState;

// declared the CPU that will be used.
extern machineState CPU;

// struct to hold shift function results.
typedef struct {
    word result;
    bool carryout;
} shiftRes;


// Register enums for quick access
typedef enum {
    SP = 13,
    LR = 14,
    PC = 15
} reg;

// condition mnemonics
typedef enum {
    EQ = 0,
    NE = 1,
    GE = 10,
    LT = 11,
    GT = 12,
    LE = 13,
    AL = 14
} condition;

// opcode mnemonics note: very messy, big dislike, not poguers
typedef enum {
    AND = 0, EOR, SUB, RSB, ADD,
    TST = 8, TEQ, CMP,
    ORR = 12, MOV
} opcode;

typedef enum {
    INVALID_INSTR = 1,
    INVALID_ARGUMENTS,
    NON_TERMINATION,
    INVALID_FILE,
    CORRUPT_FILE,
    INVALID_REG_ACCESS
} errors;

// UTILITIES:

/* 
case match: {ops}; break;
For making switch statements less tedious
@param match The value to match
@param ops The code to run, and then break after
*/
#define CASEBREAK(match, ops) case match: ops; break;

/* Return a range of bits.
@param data Source string of bits
@param start inclusive start
@param n number of bits
*/
#define GETBITS(data, start, n) (((data) >> (start)) & ((1 << (n)) - 1))

/* get bit at location in a word:
@param data the word you are inspecting
@param n bit number (0-31) 
*/
#define GETBIT(data, n) (((data) >> (n)) % 2 != 0)

/* 
Set the CPSR values as once
@param n (N)egative bit
@param z (Z)ero bit
@param c (C)arry bit
@param v O(v)erflow bit
*/
#define SETCPSR(n, z, c, v) CPU.CPSR.N = n;CPU.CPSR.Z = z;CPU.CPSR.C = c;CPU.CPSR.V = v;


// memory access macros:

/* 
Get a pointer to a register.
@param Reg <- either enum reg or
*/
#define GETREG(reg) (CPU.registers + reg)

/* 
Get data stored at a given location
@param loc location in 64KB memory
*/
#define MEMLOC(loc) (CPU.memory + loc)

#define MEMWORD(loc) ((word *) MEMLOC(loc))

// INSTRUCTION PROCESSING:

/* 
Load the program into memory
@param filename The name/path of the binary to be loaded
*/
void loadProgram(char* filename);


/* 
Run the program starting at start, determine instruction condition and 
format, and send to relevant function.
*/
void runProgram(void);


/* 
Check that an instruction's condition code can proceed
@param instr instruction to check
@retval true if instruction should be run, false otherwise.
*/
bool checkCond(instruction instr);


/* 
Execute a branch instruction
@param instr instruction to process
*/
void branchInstr(instruction instr);


/* 
Execute a Single Data Transfer instruction
@param instr instruction to process
*/
void singleDataTransInstr(instruction instr);

/* 
Given a shift pattern (bits 11-0 of data processing operand when Operand 2 is 
a register), Compute the shift operand value.

@param shift Instruction bits 11-0 (inclusive)
@retval a struct of the shift, and overflow bit
*/
shiftRes shiftOperation(word shift);

/* 
Execute a multiply instruction
@param instr instruction to process
*/
void multiplyInstr(instruction instr);

/* 
Execute an arithmetic instruction based on opcode provided
@param instr instruction to process
*/
void processDataInstr(instruction instr);

// TERMINAL OUTPUT:

/* 
Print the state of the CPU to the terminal
*/
void printState(void);

/*

*/

#endif