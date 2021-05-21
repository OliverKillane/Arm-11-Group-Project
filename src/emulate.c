#include <stdlib.h>
#include <stdio.h>
#include "emulate.h"


machineState CPU;

// edit needs to be tested, make more robust
program getProgram(char* filename) {
  FILE *file = fopen(filename, "rb");

  if (!file) {
    perror("could not open file");
    exit(EXIT_FAILURE);
  }

  //create program
  program prog;

  // go to end of file, get length (number of bytes)
  fseek(file, 0, SEEK_END);

  //get size in bytes of program
  int length = ftell(file);

  // create buffer for instructions of adequet size
  prog.start = malloc(length);

  // get instruction to halt at
  prog.end = prog.start + (length >> 2);

  // return to the start of the file
  fseek(file, 0, SEEK_SET);

  // read file into buffer starting at prog.instructions
  fread(prog.start, 1, length, file);

  //close file
  fclose(file);

  //return the program
  return prog;
}

void runProgram(program prog) {
  instruction *currentPointer = prog.start;
  instruction currentInstruction;

  do {
    if (prog.end < currentPointer) {
      perror("Program does not terminate, has surpassed instructions without halt");
      exit(NON_TERMINATION);
    }

    currentInstruction = *currentPointer;

    currentPointer++;

    if(GETBITS(currentInstruction, 24, 4) == 0xA) {
      
      //Branch
      branchInstr(currentInstruction, &currentPointer);

    } else if(GETBITS(currentInstruction, 26, 2) && !GETBITS(currentInstruction, 21, 2)) {
      
      //Single Data Transfer
      singleDataTransInstr(currentInstruction);

    } else if(!GETBITS(currentInstruction, 22, 6) && GETBITS(currentInstruction, 4, 4) == 0x9) {
      
      // Multiply
      multiplyInstr(currentInstruction);

    } else if(!GETBITS(currentInstruction, 26, 2)) {
      
      // Data Processing
      processDataInstr(currentInstruction);

    } else {
      
      // Invalid instruction
      perror("Invalid instruction no: %x", currentInstruction);
      exit(INVALID_INSTR);
    }

    // set PC to 2 instructions ahead
    *getReg(PC) = prog.start - currentPointer + 2;

  } while(currentInstruction);
}

bool checkCond(condition cond) {
  switch(cond) {
    case EQ: return CPU.CPSR.Z;
    case NE: return !CPU.CPSR.Z;
    case GE: return CPU.CPSR.N == CPU.CPSR.V;
    case LT: return CPU.CPSR.N != CPU.CPSR.V;
    case GT: return !CPU.CPSR.Z && (CPU.CPSR.N == CPU.CPSR.V);
    case LE: return CPU.CPSR.Z || (CPU.CPSR.N != CPU.CPSR.V);
    case AL: return true;
    default: return false;
  }
}

void branchInstr(instruction inst, instruction **currentInstr) {}

void singleDataTransInstr(instruction inst) {}

void multiplyInstr(instruction inst) {}

void processDataInstr(instruction inst) {
}

inline word *getReg(reg Reg) {
  return &CPU.registers[Reg];
}

inline void storemem(location loc, word data) {
  CPU.memory[loc] = data;
}

inline word getmem(location loc) {
  return CPU.memory[loc];
}

void printState() {}

