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

    // set PC to 2 instructions ahead
    *(getReg(PC)) = prog.start - currentPointer + 2;

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
      fprintf(stderr, "Invalid instruction no: %x", currentInstruction);
      exit(INVALID_INSTR);
    }

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

void branchInstr(instruction instr, instruction **currentInstr) {
  int offset = (GETBITS(instr, 0, 23) - GETBIT(instr, 23) << 23) << 2;
  
  // update the PC by offset
  *getReg(PC) += offset;

  // the currentInstr goes to the PC's position
  *currentInstr += offset + offset > 0? 2 : -2;
}

// ISSUE: needs to be tested
void singleDataTransInstr(instruction instr) {
  word* RdBase = getReg((reg)GETBITS(instr, 12, 4));
  word* RnSrcDst = getReg((reg)GETBITS(instr, 16, 4));
  int offset;
  bool I = GETBIT(instr, 25);
  bool P = GETBIT(instr, 24);
  bool U = GETBIT(instr, 23);
  bool L = GETBIT(instr, 20);

  
  // cannot use PC as Rd, Rn
  if (RdBase == getReg(PC) || RnSrcDst == getReg(PC)) {
    fprintf(stderr, "Data Transfer instruction uses PC as Rd/Rn: %x", instr);
    exit(INVALID_INSTR);
  }

  // Determine the shift offset, if bit 25 = 1, then interpret as a shift register, else as an integer.

  if (I) {

    // if post idexing, using shift, Rn != Rm
    if (getReg((reg)GETBITS(instr, 0, 4)) == RnSrcDst && !P) {
      fprintf(stderr, "Data Transfer instruction uses same register as Rn, Rm: %x", instr);
      exit(INVALID_INSTR);
    }

    offset = shiftOperation(instr);
  } else {
    offset = GETBITS(instr, 0, 12);
  }

  if (!U) {
    offset = -offset;
  }

  if (P) {
    // pre-indexing
    if (L) {
      *RnSrcDst = getmem(*RdBase + offset);
    } else {
      storemem(*RdBase + offset, *RnSrcDst);
    }
  } else {
    // POST Indexing
    if (L) {
      *RnSrcDst = getmem(*RdBase);
    } else {
      storemem(*RdBase, *RnSrcDst);
    }
    *RdBase += offset;
  }
}


word shiftOperation(word shift) {
  // get Rm register value and shift type

  word *Rm = getReg((reg)GETBITS(shift, 0, 4));

  if (Rm == getReg(PC)) {
    // Cannot have reg be the PC

    perror("Invalid instruction, shift has Rm as PC: %x");
    exit(INVALID_INSTR);
  }

  word RmVal = *Rm;
  byte shiftType = GETBITS(shift, 5, 2);
  word shiftby;

  // Check 4th bit to determine the shoft type (integer or register)
  if (GETBIT(shift, 4) && !GETBIT(shift, 7)) {

    // shift by value of selected register
    shiftby = *(getReg((reg)GETBITS(shift, 8, 4)));

  } else if (!GETBIT(shift, 4)) {

    // shift by constant integer amount
    shiftby = GETBITS(shift, 7, 5);

  } else {
    // as it is neither an integer or register shift, it is invalid
    perror("Data processing instruction has an invalid shift.");
    exit(INVALID_INSTR);
  }

  switch(shiftType) {
    case 0: return RmVal << shiftby;
    case 1: return RmVal >> shiftby;
    case 2: return (RmVal >> shiftby) + GETBIT(RmVal, 31)?MAXINT32 << (32 - shiftby):0;
    case 3: return (RmVal >> shiftby) + GETBITS(RmVal, 0, shiftby) << (MAXINT32 - shiftby);
  }
}


void multiplyInstr(instruction instr) {
  word *Rd = getReg((reg)GETBITS(instr, 16, 4));
  word *Rm = getReg((reg)GETBITS(instr, 0, 4));
  word *Rs = getReg((reg)GETBITS(instr, 8, 4));
  word *Rn = getReg((reg)GETBITS(instr, 12, 4));
  word *PCReg = getReg(PC);


  if (Rd == Rm || PCReg == Rd || PCReg == Rm || PCReg == Rs || PCReg == Rn) {
    fprintf(stderr, "Multiply instruction uses same register for Rd, Rm: %x", instr);
    exit(INVALID_INSTR);
  }

  bool A = GETBIT(instr, 21);
  bool S = GETBIT(instr, 20);

  // result = Rm \* Rs
  word result = *Rm * *Rs;

  if (A) {
    // if accumulate, add Rn
    result += *Rn;
  }

  // set result
  *Rd = result;

  if (S) {
    CPU.CPSR.N = GETBIT(result, 31);
    CPU.CPSR.Z = result == 0;
  }
}

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

