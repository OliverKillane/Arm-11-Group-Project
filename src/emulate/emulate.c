#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "emulate.h"

machineState CPU;

/* TEST allows for test suite to run unit tests without double definition of main */
#ifndef TEST
int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Error: Invalid number of arguments provided, need only one filename\n");
    exit(INVALID_ARGUMENTS);
  }

  /* set up machine initial state */
  CPU.CPSR = (cpsr) {.N = 0, .Z = 0, .C = 0, .V = 0};
  CPU.memory = calloc(MEMSIZE, 1);
  assert(CPU.memory);
  memset(CPU.registers, 0, 64);
  CPU.GPIO = 0;
  
  /*load, run and display final state */
  loadProgram(argv[1]);
  runProgram();
  printState();

  /* CPU memory is the only memory on the heap allocated, so it must be freed */
  free(CPU.memory);

  return EXIT_SUCCESS;
}
#endif


void loadProgram(char* filename) {

  /* open the file and perform null check */
  FILE *file = fopen(filename, "rb");

  if (!file) {
    printf("Error: could not open file\n");
    exit(INVALID_FILE);
  }

  /* get file length*/
  fseek(file, 0, SEEK_END);
  int length = ftell(file);
  fseek(file, 0, SEEK_SET);

  /* read file contents */
  if (fread(CPU.memory, 1, length, file) != length) {
    printf("Error: Unable to load all instructions\n");
    exit(INVALID_FILE);
  }

  /* if the system is not little endian, reorder instruction bytes accordingly*/
  if (!littleendiancheck()) {
    byte* memloc;
    byte holder;

    /* for each memory location, swap order of bytes from 0123 to 3210 */
    for (int loc = 0; loc < length; loc += 4) {
      memloc = getmemloc(loc);

      holder = memloc[0];
      memloc[0] = memloc[3];
      memloc[3] = holder;

      holder = memloc[1];
      memloc[1] = memloc[2];
      memloc[2] = holder;
    }
  }

  /* close the file */
  fclose(file);
}

void runProgram() {

  /* to mimic pipelining, PC starts at 4 */
  *GETREG(PC) = 4;
  instruction currentInstr;

  /* run fetch-decode-execute loop until at halt instruction, (all zeros) */
  do {

    /* increment PC and fetch instruction */
    *GETREG(PC) += 4;
    currentInstr = *getmemword(*GETREG(PC) - 8);

    /* if instruction condition is satisfied, decide which type and process*/
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
        printf("Error: Invalid instruction type: %08x\n", currentInstr);
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

  /* increase PC by sign extended operand, multiplied by 4*/
  *GETREG(PC) += (GETBITS(instr, 0, 23) - (GETBIT(instr, 23) << 23) + 1) << 2;
}


void singleDataTransInstr(instruction instr) {
  word* RnBase = GETREG(GETBITS(instr, 16, 4));
  word* RdSrcDst = GETREG(GETBITS(instr, 12, 4));
  int offset;
  bool I = GETBIT(instr, 25);
  bool P = GETBIT(instr, 24);
  bool U = GETBIT(instr, 23);
  bool W = GETBIT(instr, 21);
  bool L = GETBIT(instr, 20);

  /* FATAL ERROR: PC cannot be the destination register */
  if (RdSrcDst == GETREG(PC)) {
    printf("Error: Data Transfer instruction uses PC as Rd: %08x\n", instr);
    printState();
    exit(INVALID_INSTR);
  }

  if (I) {
    /* FATAL ERROR: if post idexing, using shift, Rn != Rm */
    if (GETREG(GETBITS(instr, 0, 4)) == RdSrcDst && !P) {
      printf("Error: Data Transfer instruction uses same register as Rn, Rm: %08x\n", instr);
      printState();
      exit(INVALID_INSTR);
    }
    offset = shiftOperation(instr).result;
  } else {
    offset = GETBITS(instr, 0, 12);
  }

  if (!U) {
    offset = -offset;
  }

  word memloc;
  if (P) {

    /* if pre indexing, pre index, use W bit to determine if to update Rn*/
    memloc = *RnBase + offset;
    if (W) {
      *RnBase += offset;
    }
  } else {
    
    /* if post indexing, post index and update Rn */
    memloc = *RnBase;
    *RnBase += offset;
  }

  if (memloc == 0x20200008 || memloc == 0x20200004 || memloc == 0x20200000) {
    int region = ((memloc & 0xF) >> 2) * 10;
    printf("One GPIO pin from %i to %i has been accessed\n", region, region + 9);

    if (L) {
      *RdSrcDst = memloc;
    }

    /* store is ignored as all loads must load the address, so stored values do not matter. */
  } else if (memloc == 0x20200028 && !L) {
    
    /* clear pins */
    printf("PIN OFF\n");
    CPU.GPIO = CPU.GPIO & !*RdSrcDst;
  } else if (memloc == 0x2020001C && !L) {

    /* set pins */
    printf("PIN ON\n");
    CPU.GPIO = CPU.GPIO | *RdSrcDst;
  } else if (memloc < MEMSIZE) {

    /* interacting with 64KB of main memory */
    if (L) {
      *RdSrcDst = *getmemword(memloc);
    } else {
      *getmemword(memloc) = *RdSrcDst;
    }
  } else {

    /* not a load/store to control, or a store to clear or set, and
    address is outside 64KB main memory */

    printf("Error: Out of bounds memory access at address 0x%08x\n", memloc);
    return;
  }
}


shiftRes shiftOperation(instruction shift) {
  word *Rm = GETREG(GETBITS(shift, 0, 4));

  if (Rm == GETREG(PC)) {
    printf("Error: invalid shift uses PC as Rm: 0x%08x\n", shift);
    exit(INVALID_INSTR);
  }

  word RmVal = *Rm;
  byte shiftType = GETBITS(shift, 5, 2);
  word shiftby;

  /* Check 4th bit to determine the shift type (integer or register) */
  if (GETBIT(shift, 4) && !GETBIT(shift, 7)) {

    /* shift by value of selected register */
    shiftby = *(GETREG(GETBITS(shift, 8, 4)));

  } else if (!GETBIT(shift, 4)) {
    
    /* shift by constant integer amount */
    shiftby = GETBITS(shift, 7, 5);

  } else {

    printf("Error: Data processing instruction has an invalid shift: 0x%08x\n", shift);
    exit(INVALID_INSTR);
  }

  /* checking for shift by zero */
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
      printf("Error: Invalid shift: 0x%08x\n", shift);
      exit(INVALID_INSTR);
  }
}

void multiplyInstr(instruction instr) {
  word *Rd = GETREG(GETBITS(instr, 16, 4));
  word *Rm = GETREG(GETBITS(instr, 0, 4));
  word *Rs = GETREG(GETBITS(instr, 8, 4));
  word *Rn = GETREG(GETBITS(instr, 12, 4));
  word *PCReg = GETREG(PC);

  /* FATAL ERROR: cannot have instruction with this register usage */
  if (Rd == Rm || PCReg == Rd || PCReg == Rm || PCReg == Rs || PCReg == Rn) {
    printf("Error: Multiply instruction uses same register for Rd, Rm: %08x\n", instr);
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
  opcode instrOpCode = GETBITS(instr, 21,4);
  word *Rd = GETREG(GETBITS(instr, 12, 4));
  word RnVal = *GETREG(GETBITS(instr, 16, 4));
  word operand2Value;
  word result;

  bool I = GETBIT(instr, 25);
  bool S = GETBIT(instr, 20);
  bool shiftCarryOut = false;
    
  if(I){

    /* Operand2 is an immediate value (shift rotate by rotate * 2) */
    word rotate = GETBITS(instr, 8, 4) << 1;
    word imm = GETBITS(instr, 0, 8);
    operand2Value = (imm >> rotate) | (GETBITS(imm, 0, rotate) << (32 - rotate)); 

    if(rotate > 0){
      shiftCarryOut = GETBIT(imm, rotate - 1);
    }

  } else {

    /* Operand 2 is a shift register */
    shiftRes op2 = shiftOperation(instr);
    operand2Value = op2.result;
    shiftCarryOut = op2.carryout;
  }

  /* Perform ALU operation */
  switch(instrOpCode){
    case TST:
    case AND: 
      result = RnVal & operand2Value; 
      break;
    case TEQ:
    case EOR:
      result = RnVal ^ operand2Value; 
      break;
    case CMP:
    case SUB: 
      result = RnVal - operand2Value; 
      break;
    case RSB: 
      result = operand2Value - RnVal; 
      break;
    case ADD: 
      result = RnVal + operand2Value; 
      break;
    case ORR: 
      result = RnVal | operand2Value; 
      break;
    case MOV: 
      result = operand2Value;
      break;
    default: 

      /* FATAL ERROR: cannot determine instruction type so exit */
      printf("Error: Invalid operation in instruction: %08x\n", instr);
      exit(INVALID_INSTR);
  }

  /* if instruction impacts destination register, write to destination */
  if (instrOpCode != CMP && instrOpCode != TEQ && instrOpCode != TST) {
    *Rd = result;
  }

  /* if S set then reassign CPSR flags */
  if(S) {
    if (instrOpCode == AND || instrOpCode == EOR || instrOpCode == ORR || instrOpCode == TEQ || instrOpCode == TST || instrOpCode == MOV) {
      CPU.CPSR.C = shiftCarryOut;
    } else if (instrOpCode == ADD || instrOpCode == RSB) {
      CPU.CPSR.C = (GETBIT(RnVal, 31) || GETBIT(operand2Value, 31)) && !GETBIT(result, 31);
    } else {
      /* Opcode must BE SUB or CMP */
      CPU.CPSR.C = operand2Value <= RnVal;
    }

    CPU.CPSR.Z = result == 0;
    CPU.CPSR.N = GETBIT(result, 31);
  }
}

void printState() {

  /* orint out each register, except for LR and SP*/
  printf("Registers:\n");
  for (int registerNo = 0; registerNo < 13; registerNo++) {
    printf("$%-3i: %10i (0x%08x)\n", registerNo, *GETREG(registerNo), *GETREG(registerNo));
  }
  printf("PC  : %10i (0x%08x)\n", *GETREG(PC), *GETREG(PC));

  word cpsrReg = ((CPU.CPSR.N << 3) + (CPU.CPSR.Z << 2) + (CPU.CPSR.C << 1) + CPU.CPSR.V) << 28;
  printf("CPSR: %10i (0x%08x)\n", cpsrReg, cpsrReg);

  /* print out the memory, note: on big endian systems, this memory will be printed as big endian */
  printf("Non-zero memory:\n");

  bool littleEndian = littleendiancheck();
  byte *memByte;
  for (int loc = 0; loc < MEMSIZE; loc += 4) {
    memByte = getmemloc(loc);
    if (*(word*)memByte){

      /* if little endian, print out in order, if big, swap bytes to mimic little endian */
      if (littleEndian) {
        printf("0x%08x: 0x%02x%02x%02x%02x\n", loc, memByte[0], memByte[1], memByte[2], memByte[3]);
      } else {
        printf("0x%08x: 0x%02x%02x%02x%02x\n", loc, memByte[3], memByte[2], memByte[1], memByte[0]);
      }
    }
  }
}

bool littleendiancheck() {
    word test = 1;
    return *((byte*) &test);
}

word *getmemword(location loc) {
  return (word *) getmemloc(loc);
}

byte *getmemloc(location loc) {
  return (CPU.memory + loc);
}
