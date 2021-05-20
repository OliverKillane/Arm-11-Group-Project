#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>
#include <stdbool.h>

// TYPE DECLARATIONS:
// type definitions for readability
typedef uint32_t word;
typedef uint32_t instruction;
typedef uint16_t location;

// Hold the state of the emulator
//CPSR = NZCV
typedef struct {
    word registers[16];
    char CPSR;
    word *memory; 
} machineState;

// declared the CPu that will be used.
extern machineState CPU;

typedef struct {
    instruction *start;
    instruction *end;
} program;

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

// CPSR code mnemonics
typedef enum {
    V = 1,
    C = 2,
    Z = 4,
    N = 8
} CPSRcode;

// UTILITIES:
/* GETBITS
Return a range of bits.
    data    <- Source string of bits
    start   <- inclusive start
    n       <- number of bits
*/
#define GETBITS(data, start, n) ((data >> start) & (1 << n - 1))


// INSTRUCTION PROCESSING:

/* Return a pointer to the start of the program instructions:
    filename <- name of the file to load 
*/
program getProgram(char* filename);


/* Run the program starting at start
    start <- pointer to array of instructions
*/
void runProgram(program prog);


/* Check that an instruction's condition code can proceed
    cond <- condition code
*/
bool checkCond(condition cond);

/* Determine the type of instruction and run function accordingly
    instr <- instruction to process
*/
void processInstr(instruction instr);


/* Execute a branch instruction
    instr <- instruction to process
*/
void branchInstr(instruction inst, instruction *currentInstr);


/* Execute a Single Data Transfer instruction
    instr <- instruction to process
*/
void singleDataTransInstr(instruction inst);


/* Execute a multiply instruction
    instr <- instruction to process
*/
void multiplyInstr(instruction inst);


/* Execute an arithmetic instruction based on opcode provided
    instr <- instruction to process
*/
void processDataInstr(instruction inst);


// MACHINE STATE ACCESS:
/* Get a pointer to a register.
    Reg <- either enum reg or 
*/
inline word *getReg(reg Reg);

/* Store a given word in a given memory location
    loc     <- location in 64KB memory to
    data    <- Data top write
*/
inline void storemem(location loc, word data);

/* Get data stored at a given location
    loc <- location in 64KB memory
*/
inline word getmem(location loc);

// TERMINAL OUTPUT:

/* print the state of the CPU to the terminal
*/
void printState();

#endif