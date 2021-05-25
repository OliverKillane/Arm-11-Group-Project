#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulate.h"

machineState CPU;

#ifndef TEST
int main(int argc, char** argv) {
  if (argc != 2) {
    perror("Invalid number of arguments provided, need only one filename");
    exit(INVALID_ARGUMENTS);
  }

  CPU.CPSR = (cpsr) {.N = 0, .Z = 0, .C = 0, .V = 0};
  CPU.memory = calloc(MEMSIZE, 1);
  assert(CPU.memory);
  memset(CPU.registers, 0, 64);

  loadProgram(argv[1]);
  runProgram();
  printState();

  return EXIT_SUCCESS;
}
#endif


void loadProgram(char* filename) {
  FILE *file = fopen(filename, "rb");

  if (!file) {
    perror("could not open file");
    exit(INVALID_FILE);
  }

  fseek(file, 0, SEEK_END);

  int length = ftell(file);

  fseek(file, 0, SEEK_SET);

  if (fread(CPU.memory, 1, length, file) != length) {
    perror("Unable to load all instructions");
    exit(INVALID_FILE);
  }

  fclose(file);
}

void runProgram() {
  *GETREG(PC) = 4;
  instruction currentInstr;

  do {
    *GETREG(PC) += 4;
    currentInstr = *getmemword(*GETREG(PC) - 8);

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

void branchInstr(instruction instr) {
  int offset = (GETBITS(instr, 0, 23) - (GETBIT(instr, 23) << 23)) << 2;
  *GETREG(PC) += offset + 4;
}

void singleDataTransInstr(instruction instr) {
  word* RnBase = GETREG(GETBITS(instr, 16, 4));
  word* RdSrcDst = GETREG(GETBITS(instr, 12, 4));
  int offset;
  bool I = GETBIT(instr, 25);
  bool P = GETBIT(instr, 24);
  bool U = GETBIT(instr, 23);
  bool L = GETBIT(instr, 20);

  if (RdSrcDst == GETREG(PC)) {
    fprintf(stderr, "Data Transfer instruction uses PC as Rd: %x", instr);
    exit(INVALID_INSTR);
  }

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

  if (!U) offset = -offset;

  if (P) {
    // pre-indexing
    if (L) {
      *RdSrcDst = *getmemword(*RnBase + offset);
    } else {
      *getmemword(*RnBase + offset) =  *RdSrcDst;
    }
  } else {
    // POST Indexing
    if (L) {
      *RdSrcDst = *getmemword(*RnBase);
    } else {
      *getmemword(*RnBase) =  *RdSrcDst;
    }
    *RnBase += offset;
  }
}


shiftRes shiftOperation(word shift) {
  word *Rm = GETREG(GETBITS(shift, 0, 4));

  if (Rm == GETREG(PC)) {
    perror("Invalid instruction, shift has Rm as PC: %x");
    exit(INVALID_INSTR);
  }

  word RmVal = *Rm;
  byte shiftType = GETBITS(shift, 5, 2);
  word shiftby;

  // Check 4th bit to determine the shift type (integer or register)
  if (GETBIT(shift, 4) && !GETBIT(shift, 7)) {
    // shift by value of selected register
    shiftby = *(GETREG(GETBITS(shift, 8, 4)));
  } else if (!GETBIT(shift, 4)) {
    // shift by constant integer amount
    shiftby = GETBITS(shift, 7, 5);
  } else {
    perror("Data processing instruction has an invalid shift.");
    exit(INVALID_INSTR);
  }

  // checking for shift by zero
  if (shiftby == 0) {
    return (shiftRes) {
      .result = RmVal,
      .carryout = 0
    };
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

  word result = *Rm * *Rs + (A?*Rn:0);
  *Rd = result;

  if (S) {
    CPU.CPSR.N = GETBIT(result, 31);
    CPU.CPSR.Z = result == 0;
  }
}

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

  // Perform ALU operation
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

  // if S set then reassign CPSR flags
  if(S) {
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

void printState() {
  printf("Registers:");
  for (int registerNo = 0; registerNo < 13; registerNo++) {
    printf("\n$%-3i: %10i (0x%08x)", registerNo, *GETREG(registerNo), *GETREG(registerNo));
  }
  printf("\nPC  : %10i (0x%08x)", *GETREG(PC), *GETREG(PC));

  word cpsrReg = ((CPU.CPSR.N << 3) + (CPU.CPSR.Z << 2) + (CPU.CPSR.C << 1) + CPU.CPSR.V) << 28;
  printf("\nCPSR: %10i (0x%08x)", cpsrReg, cpsrReg);

  printf("\nNon-zero memory:");
  byte *wordMem;
  for (int loc = 0; loc < MEMSIZE; loc += 4) {
    wordMem = getmemloc(loc);
    if (*((word*)wordMem)){
      printf("\n0x%08x: 0x%02x%02x%02x%02x", loc, wordMem[0], wordMem[1], wordMem[2], wordMem[3]);
    }
  }
}

word *getmemword(location loc) {
    return ((word *) getmemloc(loc));
}

byte *getmemloc(location loc) {
    return (CPU.memory + loc);
}


