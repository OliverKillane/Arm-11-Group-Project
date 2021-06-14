#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>
#include <stdbool.h>
#include "SDL.h"

// TYPE DECLARATIONS:
// type definitions for readability
typedef uint32_t word;
typedef uint32_t instruction;
typedef uint16_t location;
typedef uint8_t byte;

// 524KB memory (16 bit address)
#define MEMSIZE (1 << 19)

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
    word GPIO;
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

// opcode mnemonics for the processData instruction
typedef enum {
    AND = 0, EOR, SUB, RSB, ADD,
    TST = 8, TEQ, CMP,
    ORR = 12, MOV
} opcode;

typedef enum {
    INVALID_INSTR = 1,
    INVALID_ARGUMENTS,
    INVALID_FILE,
    CORRUPT_FILE,
    INVALID_REG_ACCESS
} errors;

// EMULATOR MODES:
typedef enum {
    DEFAULT = 0,
    GPIO_EXTENDED = 1,
    VIDEO = 2
} modes;

// declare the emulator Mode.
extern modes emulatorMode;


// UTILITIES:

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
#define GETBIT(data, n) (((data) >> (n)) & 1)

/* 
Get a pointer to a register.
@param Reg <- either enum reg or
*/
#define GETREG(reg) (CPU.registers + reg)


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
shiftRes shiftOperation(instruction shift);

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

// EMULATOR DATA ACCESS:

/* return the word (32 bits) starting at byte loc (16 bit location)
 Can never segfault as 16 bit address.
@param loc 16bit location in memory
@retval pointer to word in memory
*/
word *getmemword(word loc);


/* Get the byte at loc (16 bit location)
 Can never segfault as 16 bit address.
@param loc 16bit location in memory
@retval pointer to byte in memory
*/
byte *getmemloc(word loc);


/*  determine if the system the emulator is being run on is big or little endian 
@retval true if little endian system, false otherwise (big endian)
*/
bool littleendiancheck(void);

/* free the memory associated with the CPU struct.
*/
void freeCPU(void);

// TERMINAL OUTPUT:

/* 
Print the state of the CPU to the terminal
*/
void printState(void);

// VIDEO OUTPUT:
/* Window Size, in pixels */
#define HEIGHT 108
#define WIDTH 192

#define WINDOW_HEIGHT 432
#define WINDOW_WIDTH 768

/* the address containing the pointer to the start of the display. */
#define VIDEO_POINTER 0x1000000
#define INPUT_BUFFER 0x30000
#define INPUT_BUFFER_SIZE 64


/* the 3 main variables required, the window, the renderer to draw to the window, 
 * and the texture to be drawn by the renderer */
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern byte* video_pointer;


/* Initialise the window, renderer and the texture*/
void setupWindow(char *title);


/* Update the window to display the current video out */
void updateOutput(void);


/* Take the events that have happened since the last call, if characters,
 * add to character buffer*/
void processEvents(void);

/* close the window, and remove the associated renderer, textures */
void destroyVideo(void);

#endif
