#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulate.h"

machineState CPU;

#ifndef TEST
int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Error: Invalid number of arguments provided, need only one filename\r\n");
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
    printf("Error: could not open file\r\n");
    exit(INVALID_FILE);
  }

  fseek(file, 0, SEEK_END);

  int length = ftell(file);

  fseek(file, 0, SEEK_SET);

  if (fread(CPU.memory, 1, length, file) != length) {
    printf("Error: Unable to load all instructions\r\n");
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
        printf("Error: Invalid instruction no: %08x\r\n", currentInstr);
        printState();
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
  *GETREG(PC) += (GETBITS(instr, 0, 23) - (GETBIT(instr, 23) << 23) + 1) << 2;
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
    printf("Error: Data Transfer instruction uses PC as Rd: %08x\r\n", instr);
    printState();
    exit(INVALID_INSTR);
  }

  if (I) {
    // if post idexing, using shift, Rn != Rm
    if (GETREG(GETBITS(instr, 0, 4)) == RdSrcDst && !P) {
      printf("Error: Data Transfer instruction uses same register as Rn, Rm: %08x\r\n", instr);
    }
    offset = shiftOperation(instr).result;
  } else {
    offset = GETBITS(instr, 0, 12);
  }

  if (!U) {
    offset = -offset;
  }

  word loc = P?(*RnBase + offset):*RnBase;

  if (loc >= MEMSIZE) {
    printf("Error: Out of bounds memory access at address 0x%08x\r\n", loc);
  } else {
    if (L) {
      *RdSrcDst = *getmemword(loc);
    } else {
      *getmemword(loc) = *RdSrcDst;
    }

    if (!P) {
      *RnBase += offset;
    }
  }
 
}


shiftRes shiftOperation(word shift) {
  word *Rm = GETREG(GETBITS(shift, 0, 4));

  if (Rm == GETREG(PC)) {
    printf("Error: invalid shift uses PC as Rm");
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

    printf("Error: Data processing instruction has an invalid shift.\r\n");
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
      printf("Error: Invalid shift");
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
    printf("Error: Multiply instruction uses same register for Rd, Rm: %08x\r\n", instr);
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
    case AND: 
      ALUOut = RnVal & operand2Value; 
      *Rd = ALUOut;
      break;
    case EOR:
      ALUOut = RnVal ^ operand2Value; 
      *Rd = ALUOut;
      break;
    case SUB: 
      ALUOut = RnVal - operand2Value; 
      *Rd = ALUOut;
      break;
    case RSB: 
      ALUOut = operand2Value - RnVal; 
      *Rd = ALUOut;
      break;
    case ADD: 
      ALUOut = RnVal + operand2Value; 
      *Rd = ALUOut;
      break;
    case TST: 
      ALUOut = RnVal & operand2Value;
      break;
    case TEQ: 
      ALUOut = RnVal ^ operand2Value;
      break;
    case CMP: 
      ALUOut = RnVal - operand2Value;
      break;
    case ORR: 
      ALUOut = RnVal | operand2Value; 
      *Rd = ALUOut;
      break;
    case MOV: 
      *Rd = operand2Value;
      break;
    default: 
      printf("Error: Invalid operation in instruction: %08x\r\n", instr);
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
    printf("\r\n$%-3i: %10i (0x%08x)", registerNo, *GETREG(registerNo), *GETREG(registerNo));
  }
  printf("\r\nPC  : %10i (0x%08x)", *GETREG(PC), *GETREG(PC));

  word cpsrReg = ((CPU.CPSR.N << 3) + (CPU.CPSR.Z << 2) + (CPU.CPSR.C << 1) + CPU.CPSR.V) << 28;
  printf("\r\nCPSR: %10i (0x%08x)", cpsrReg, cpsrReg);

  printf("\r\nNon-zero memory:");
  byte *wordMem;
  for (int loc = 0; loc < MEMSIZE; loc += 4) {
    wordMem = getmemloc(loc);
    if (*(word*)wordMem){
      printf("\r\n0x%08x: 0x%02x%02x%02x%02x", loc, wordMem[0], wordMem[1], wordMem[2], wordMem[3]);
    }
  }
}

word *getmemword(location loc) {
  return ((word *) getmemloc(loc));
}

byte *getmemloc(location loc) {
  return (CPU.memory + loc);
}