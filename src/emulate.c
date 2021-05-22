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

  // TODO: check that jump is valid (Need more here).

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

//TODO: error handling especially for PC
void processDataInstr(instruction inst) {
  
    bool I = GETBITS(inst, 25, 1);
    opcode OpCode = GETBITS(inst, 21,4);
    bool S = GETBITS(inst, 20, 1);
    word *Rn = getReg((reg) GETBITS(inst, 16, 4));
    word *Rd = getReg((reg) GETBITS(inst, 12, 4));
    word operand2Field = GETBITS(inst, 0, 12);

    word operand2Value;
    word ALUOut;
    bool shiftCarryOut = 0;
    bool ALUcarryOut = 0;

    
    //Operand2 is an immediate value
    if(I){
      char rotate = GETBITS(operand2Field, 8, 4) * 2;
      word imm = GETBITS(operand2Field, 0, 8);
      imm = imm >> rotate + GETBITS(imm, 0, rotate) << (32 - rotate); 
      operand2Value = imm;
    }
    //Operand2 is a register
    else{
      word shift = GETBITS(operand2Field, 4, 8);
      word *Rm = getReg((reg) GETBITS(operand2Field, 0, 4));

      word RmContents = *Rm;
      char shiftType = GETBITS(shift, 5, 2);
      word shiftAmmount;

      //If last bit of shift is 0 then shift ammount is an immediate value
      if(!GETBITS(shift,0,1)){
          shiftAmmount = GETBITS(shift, 7, 5);
      }

      //If last bit of shift is 1 then shift ammount is stored in a register Rs
      else{
        if(GETBITS(shift, 7, 1)){
          perror("Malformed instruction");
          exit(INVALID_INSTR);
        }
        shiftAmmount = *getReg((reg) GETBITS(shift, 8, 4));
      }

      switch(shiftType){
        //lsl
        case 0: shiftCarryOut = GETBITS(RmContents, (32-shiftAmmount), 0);
                RmContents << shiftAmmount;
                break;
        //lsr
        case 1: shiftCarryOut = GETBITS(RmContents, shiftAmmount-1, 0);
                RmContents >> shiftAmmount;
                break;
        //asr
        case 2: shiftCarryOut = GETBITS(RmContents, shiftAmmount-1, 0);
                RmContents >> shiftAmmount + GETBITS(RmContents, 31, 0)? INT32_MAX << (32 - shiftAmmount):0;
                break;
        //ror
        case 3: shiftCarryOut = GETBITS(RmContents, shiftAmmount-1, 0);
                RmContents >> shiftAmmount + GETBITS(RmContents, 0, shiftAmmount) << (32 - shiftAmmount);
                
      }
      operand2Value = RmContents;
    }

    //perform ALU operations
    switch(OpCode){
      case AND: ALUOut = *Rn & operand2Value;
                *Rd = ALUOut;
                break;
      case EOR: ALUOut = *Rn ^ operand2Value;
                *Rd = ALUOut;
                break;
      case SUB: ALUOut = *Rn - operand2Value;
                *Rd = ALUOut;
                break;
      case RSB: ALUOut = operand2Value - *Rn; 
                *Rd = ALUOut;
                break;
      case ADD: ALUOut = *Rn + operand2Value;
                *Rd = ALUOut;
                break;
      case TST: ALUOut = *Rn & operand2Value;
                break;  
      case TEQ: ALUOut = *Rn ^ operand2Value;
                break;
      case CMP: ALUOut = *Rn - operand2Value;
                break;
      case ORR: ALUOut = *Rn | operand2Value;
                *Rd = ALUOut;
                break;
      case MOV: *Rd = operand2Value;
                break;
      default: fprintf(stderr, "Invalid operation");
                exit(INVALID_INSTR);          
    }

    //if S set then reassign flags
    if(S){
      if(OpCode == AND || OpCode == EOR || OpCode == ORR || OpCode == TEQ || OpCode == TST || OpCode == MOV){
        CPU.CPSR.C = shiftCarryOut;
      }
      else if(OpCode == ADD || OpCode == RSB){
        CPU.CPSR.C = (GETBIT(*Rn, 31) || GETBIT(operand2Value, 31)) && !GETBIT(ALUOut, 31);
      }
      else if(OpCode == SUB || OpCode == CMP){
        CPU.CPSR.C = operand2Value > *Rn;
      }
      CPU.CPSR.Z = ALUOut == 0;
      CPU.CPSR.N = GETBIT(ALUOut, 31); 
    }


}

void printState() {}

