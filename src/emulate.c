#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulate.h"

machineState CPU;

// include guard for including emulate.c in emulatortests.c file.
#ifndef TEST
int main(int argc, char** argv) {
  if (argc != 2) {
    perror("Invalid number of arguments provided, need only one filename");
    exit(INVALID_ARGUMENTS);
  }

  // Setup the state of the CPU
  SETCPSR(0,0,0,0);
  CPU.memory = (byte*)calloc(1 << 16, 1);

  // ensure memory pointer is not null
  assert(CPU.memory);

  memset(CPU.registers, 0, 64);

  // Load the selectd binary into memory
  loadProgram(argv[1]);

  // Run the program from the start;
  runProgram();

  // Print out the final state of the registers and the non-zero memroy
  printState();

  //free memory section (possibly redundant)
  free(CPU.memory);

  return EXIT_SUCCESS;
}
#endif


// edit needs to be tested, make more robust
void loadProgram(char* filename) {
  FILE *file = fopen(filename, "rb");

  if (!file) {
    perror("could not open file");
    exit(INVALID_FILE);
  }

  // go to end of file, get length (number of bytes)
  fseek(file, 0, SEEK_END);

  //get size in bytes of program
  int length = ftell(file);

  // check that the instructions total is a multiple of 4 bytes.
  if (length % 4 != 0) {
    perror("File does not contain a whole number of 4 byte instructions");
    exit(CORRUPT_FILE);
  }

  // return to the start of the file
  fseek(file, 0, SEEK_SET);

  // read file into buffer starting at prog.instructions
  if (fread(CPU.memory, 1, length, file) != length) {
    perror("Unable to load all instructions");
    exit(INVALID_FILE);
  }

  //close file
  fclose(file);
}

void runProgram() {
  *GETREG(PC) = 4;
  instruction currentInstr;

  do {
    *GETREG(PC) += 4;

    currentInstr = *MEMWORD(*GETREG(PC) - 8);

    if (checkCond(currentInstr)) {
      if(GETBITS(currentInstr, 24, 4) == 0xA) {
        branchInstr(currentInstr);
      } else if(GETBITS(currentInstr, 26, 2) && !GETBITS(currentInstr, 21, 2)) {
        singleDataTransInstr(currentInstr);
      } else if(!GETBITS(currentInstr, 22, 6) && GETBITS(currentInstr, 4, 4) == 0x9) {
        multiplyInstr(currentInstr);
      } else if(!GETBITS(currentInstr, 26, 2)) {
        processDataInstr(currentInstr);
      } else {
      
        // Invalid instruction
        fprintf(stderr, "Invalid instruction no: %x", currentInstr);
        exit(INVALID_INSTR);
      }
    }
  } while(currentInstr);
}

bool checkCond(instruction instr) {
  switch(GETBITS(instr, 28, 4)) {
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

//TODO change way PC is used, allow error checking on branch
void branchInstr(instruction instr) {
  int offset = (GETBITS(instr, 0, 23) - (GETBIT(instr, 23) << 23)) << 2;
  
  // update the PC by offset, then skip forwads 2 (so instruction at PC is executed)
  *GETREG(PC) += offset + 4;
}

// ISSUE: needs to be tested
void singleDataTransInstr(instruction instr) {

  word* RnBase = GETREG(GETBITS(instr, 16, 4));
  word* RdSrcDst = GETREG(GETBITS(instr, 12, 4));
  int offset;
  bool I = GETBIT(instr, 25);
  bool P = GETBIT(instr, 24);
  bool U = GETBIT(instr, 23);
  bool L = GETBIT(instr, 20);

  
  // cannot use PC as Rd, Rn
  if (RdSrcDst == GETREG(PC)) {
    fprintf(stderr, "Data Transfer instruction uses PC as Rd: %x", instr);
    exit(INVALID_INSTR);
  }

  // Determine the shift offset, if bit 25 = 1, then interpret as a shift register, else as an integer.

  if (I) {

    // if post idexing, using shift, Rn != Rm
    if (GETREG(GETBITS(instr, 0, 4)) == RdSrcDst && !P) {
      fprintf(stderr, "Data Transfer instruction uses same register as Rn, Rm: %x", instr);
      exit(INVALID_INSTR);
    }

    offset = shiftOperation(instr).result;
  } else {
    offset = GETBITS(instr, 0, 12);
  }

  if (!U) {
    offset = -offset;
  }

  if (P) {
    // pre-indexing
    if (L) {
      *RdSrcDst = *MEMWORD(*RnBase + offset);
    } else {
      *MEMWORD(*RnBase + offset) =  *RdSrcDst;
    }
  } else {
    // POST Indexing
    if (L) {
      *RdSrcDst = *MEMWORD(*RnBase);
    } else {
      *MEMWORD(*RnBase) =  *RdSrcDst;
    }
    *RnBase += offset;
  }
}


shiftRes shiftOperation(word shift) {
  // get Rm register value and shift type

  word *Rm = GETREG(GETBITS(shift, 0, 4));

  if (Rm == GETREG(PC)) {
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
    shiftby = *(GETREG(GETBITS(shift, 8, 4)));

  } else if (!GETBIT(shift, 4)) {

    // shift by constant integer amount
    shiftby = GETBITS(shift, 7, 5);

  } else {
    // as it is neither an integer or register shift, it is invalid
    perror("Data processing instruction has an invalid shift.");
    exit(INVALID_INSTR);
  }

  switch(shiftType) {
    case 0: return (shiftRes) {
      .result = RmVal << shiftby, 
      .carryout = GETBIT(RmVal, 32 - shiftby)
      };
    case 1: return (shiftRes) {
      .result = RmVal >> shiftby, 
      .carryout = GETBIT(RmVal, shiftby - 1)
      };
    case 2: return (shiftRes) {
      .result = (RmVal >> shiftby) | (GETBIT(RmVal, 31)?(MAXINT32 << (32 - shiftby)):0),
      .carryout = GETBIT(RmVal, shiftby - 1)
      };
    case 3: return (shiftRes) {
      .result = (RmVal >> shiftby) | (GETBITS(RmVal, 0, shiftby) << (32 - shiftby)),
      .carryout = GETBIT(RmVal, shiftby - 1)
      };
    default:
      fprintf(stderr, "invalid shift : %x", shift);
      exit(INVALID_INSTR);
  }
}


void multiplyInstr(instruction instr) {
  word *Rd = GETREG(GETBITS(instr, 16, 4));
  word *Rm = GETREG(GETBITS(instr, 0, 4));
  word *Rs = GETREG(GETBITS(instr, 8, 4));
  word *Rn = GETREG(GETBITS(instr, 12, 4));
  word *PCReg = GETREG(PC);


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

//TODO: error handling especially for PC
void processDataInstr(instruction instr) {
  opcode OpCode = GETBITS(instr, 21,4);

  word *Rd = GETREG(GETBITS(instr, 12, 4));

  word RnVal = *GETREG(GETBITS(instr, 16, 4));
  word operand2Value;
  word ALUOut;

  bool I = GETBIT(instr, 25);
  bool S = GETBIT(instr, 20);

  bool shiftCarryOut = false;
    
  if(I){
    // Operand2 is an immediate value (shift rotate by rotate * 2)
    word rotate = GETBITS(instr, 8, 4) << 1;
    word imm = GETBITS(instr, 0, 8);
    operand2Value = (imm >> rotate) | (GETBITS(imm, 0, rotate) << (32 - rotate)); 
    if(rotate > 0){
    shiftCarryOut = GETBIT(imm, rotate - 1);
    }
  } else {
    // Operand 2 is a shift register
    shiftRes op2 = shiftOperation(instr);
    operand2Value = op2.result;
    shiftCarryOut = op2.carryout;
  }

  //perform ALU operations
  switch(OpCode){
    CASEBREAK(AND, ALUOut = RnVal & operand2Value; *Rd = ALUOut);
    CASEBREAK(EOR, ALUOut = RnVal ^ operand2Value; *Rd = ALUOut);
    CASEBREAK(SUB, ALUOut = RnVal - operand2Value; *Rd = ALUOut);
    CASEBREAK(RSB, ALUOut = operand2Value - RnVal; *Rd = ALUOut);
    CASEBREAK(ADD, ALUOut = RnVal + operand2Value; *Rd = ALUOut);
    CASEBREAK(TST, ALUOut = RnVal & operand2Value);
    CASEBREAK(TEQ, ALUOut = RnVal ^ operand2Value);
    CASEBREAK(CMP, ALUOut = RnVal - operand2Value);
    CASEBREAK(ORR, ALUOut = RnVal | operand2Value; *Rd = ALUOut);
    CASEBREAK(MOV, *Rd = operand2Value);
    default: 
      fprintf(stderr, "Invalid operation in instruction: %x", instr);
      exit(INVALID_INSTR);          
  }

    // if S set then reassign flags
    if(S) {

      // change CPSR based on operation
      if (OpCode == AND || OpCode == EOR || OpCode == ORR || OpCode == TEQ || OpCode == TST || OpCode == MOV) {
        CPU.CPSR.C = shiftCarryOut;
      } else if (OpCode == ADD || OpCode == RSB) {
        CPU.CPSR.C = (GETBIT(RnVal, 31) || GETBIT(operand2Value, 31)) && !GETBIT(ALUOut, 31);
      } else {
        // Opcode must BE SUB or CMP
        CPU.CPSR.C = operand2Value <= RnVal;
      }

      CPU.CPSR.Z = ALUOut == 0;
      CPU.CPSR.N = GETBIT(ALUOut, 31); 
    }
}


// For basic manual testing only as does not yet match the testing files
void printState() {
  // print out state of all registers and the non-zero memory.
  printf("Registers:");
  for (int registerNo = 0; registerNo < 13; registerNo++) {
    printf("\n$%-3i: %10i (0x%08x)", registerNo, *GETREG(registerNo), *GETREG(registerNo));
  }
  printf("\nPC  : %10i (0x%08x)", *GETREG(PC), *GETREG(PC));

  word cpsrReg = (CPU.CPSR.N << 31) + (CPU.CPSR.Z << 30) + (CPU.CPSR.C << 29) + (CPU.CPSR.V << 28);
  printf("\nCPSR: %10i (0x%08x)", cpsrReg, cpsrReg);

  printf("\nNon-zero memory:");

  word wordMem;
  for (int loc = 0; loc < MEMSIZE; loc += 4) {
    wordMem = ((unsigned int)*MEMLOC(loc) << 24) +  ((unsigned int)*MEMLOC(loc + 1) << 16) + ((unsigned int)*MEMLOC(loc + 2) << 8) + (unsigned int)*MEMLOC(loc + 3);
    if (wordMem) printf("\n0x%08x: 0x%08x", loc, wordMem);
  }
}