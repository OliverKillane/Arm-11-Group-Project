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
    *(GETREG(PC)) = prog.start - currentPointer + 2;

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

//TODO change way PC is used, allow error checking on branch
void branchInstr(instruction instr, instruction **currentInstr) {
  int offset = (GETBITS(instr, 0, 23) - GETBIT(instr, 23) << 23) << 2;
  
  // update the PC by offset
  *GETREG(PC) += offset;

  // TODO: check that jump is valid (Need more here).

  // the currentInstr goes to the PC's position
  *currentInstr += offset + offset > 0? 2 : -2;
}

// ISSUE: needs to be tested
void singleDataTransInstr(instruction instr) {
  word* RdBase = GETREG(GETBITS(instr, 12, 4));
  word* RnSrcDst = GETREG(GETBITS(instr, 16, 4));
  int offset;
  bool I = GETBIT(instr, 25);
  bool P = GETBIT(instr, 24);
  bool U = GETBIT(instr, 23);
  bool L = GETBIT(instr, 20);

  
  // cannot use PC as Rd, Rn
  if (RdBase == GETREG(PC) || RnSrcDst == GETREG(PC)) {
    fprintf(stderr, "Data Transfer instruction uses PC as Rd/Rn: %x", instr);
    exit(INVALID_INSTR);
  }

  // Determine the shift offset, if bit 25 = 1, then interpret as a shift register, else as an integer.

  if (I) {

    // if post idexing, using shift, Rn != Rm
    if (GETREG(GETBITS(instr, 0, 4)) == RnSrcDst && !P) {
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
      *RnSrcDst = MEMLOC(*RdBase + offset);
    } else {
      MEMLOC(*RdBase + offset) =  *RnSrcDst;
    }
  } else {
    // POST Indexing
    if (L) {
      *RnSrcDst = MEMLOC(*RdBase);
    } else {
      MEMLOC(*RdBase) =  *RnSrcDst;
    }
    *RdBase += offset;
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
      .carryout = GETBITS(RmVal, 32 - shiftby, shiftby)
      };
    case 1: return (shiftRes) {
      .result = RmVal >> shiftby, 
      .carryout = GETBITS(RmVal, 0, shiftby - 1)
      };
    case 2: return (shiftRes) {
      .result = (RmVal >> shiftby) + GETBIT(RmVal, 31)?MAXINT32 << (32 - shiftby):0,
      .carryout = GETBITS(RmVal, 0, shiftby - 1)
      };
    case 3: return (shiftRes) {
      .result = (RmVal >> shiftby) + GETBITS(RmVal, 0, shiftby) << (MAXINT32 - shiftby),
      .carryout = GETBITS(RmVal, 0, shiftby - 1)
      };
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

  bool shiftCarryOut = 0;
  bool ALUcarryOut = 0;
    
  if(I){
    // Operand2 is an immediate value (shift torate by rotate * 2)
    byte rotate = GETBITS(instr, 8, 4) << 1;
    word imm = GETBITS(instr, 0, 8);
    operand2Value = imm >> rotate + GETBITS(imm, 0, rotate) << (32 - rotate); 
  } else {
    // Operand 2 is a shift register
    shiftRes op2 = shiftOperation(instr);
    operand2Value = op2.result;
    shiftCarryOut = op2.carryout;
  }

  //perform ALU operations
  switch(OpCode){
    CASEB(AND, ALUOut = RnVal & operand2Value; *Rd = ALUOut)
    CASEB(EOR, ALUOut = RnVal ^ operand2Value; *Rd = ALUOut)
    CASEB(SUB, ALUOut = RnVal - operand2Value; *Rd = ALUOut)
    CASEB(RSB, ALUOut = operand2Value - RnVal; *Rd = ALUOut)
    CASEB(ADD, ALUOut = RnVal + operand2Value; *Rd = ALUOut)
    CASEB(TST, ALUOut = RnVal & operand2Value)
    CASEB(TEQ, ALUOut = RnVal ^ operand2Value)
    CASEB(CMP, ALUOut = RnVal - operand2Value) 
    CASEB(ORR, ALUOut = RnVal | operand2Value; *Rd = ALUOut)
    CASEB(MOV, *Rd = operand2Value)
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
        CPU.CPSR.C = operand2Value > RnVal;
      }

      CPU.CPSR.Z = ALUOut == 0;
      CPU.CPSR.N = GETBIT(ALUOut, 31); 
    }
}

void printState() {}

