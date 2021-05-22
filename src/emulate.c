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
        shiftAmmount = GETBITS(shift, 7, 1);
        word *Rs = getReg((reg) GETBITS(shift, 8, 4));
      }

      switch(shiftType){
        //lsl
        case 0: shiftCarryOut = GETBITS(RmContents, 31, 0);
                RmContents << shiftAmmount;
        //lsr
        case 1: shiftCarryOut = GETBITS(RmContents, shiftAmmount-1, 0);
                RmContents >> shiftAmmount;
        //asr
        case 2: shiftCarryOut = GETBITS(RmContents, shiftAmmount-1, 0);
                RmContents >> shiftAmmount + GETBITS(RmContents, 31, 0)? INT32_MAX << (32 - shiftAmmount):0;
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
      case EOR: ALUOut = *Rn ^ operand2Value;
                *Rd = ALUOut;
      case SUB: ALUOut = *Rn - operand2Value;
                *Rd = ALUOut;
      case RSB: ALUOut = operand2Value - *Rn; 
                *Rd = ALUOut;
      case ADD: ALUOut = *Rn + operand2Value;
                *Rd = ALUOut;
      case TST: ALUOut = *Rn & operand2Value;  
      case TEQ: ALUOut = *Rn ^ operand2Value;
      case CMP: ALUOut = *Rn - operand2Value;
      case ORR: ALUOut = *Rn | operand2Value;
                *Rd = ALUOut;
      case MOV: *Rd = operand2Value;
    }

    //if S set then reassign flags
    if(S){
      if(OpCode == AND || OpCode == EOR || OpCode == ORR || OpCode == TEQ || OpCode == TST || OpCode == MOV){
        CPU.CPSR.C = shiftCarryOut;
      }
      else if(OpCode == ADD || OpCode == RSB){
        CPU.CPSR.C = GETBITS(ALUOut, 31, 0);
      }
      else if(OpCode == SUB || OpCode == CMP){
        CPU.CPSR.C = !GETBITS(ALUOut, 31, 0);
      }
      CPU.CPSR.Z = ALUOut == 0;
      CPU.CPSR.N = GETBITS(ALUOut, 31, 1); 
    }


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

