#include <stdlib.h>
#include <stdio.h>
#include "emulate.h"

//decodes instruction and calls specific function for execution
void processInstr(instruction instr){

    
    //Branch
    if(GETBITS(instr, 24, 4) == 0xA){
        branchInstr(instr,getReg(PC));
    }

    //Single Data Transfer
    else if(GETBITS(instr, 26, 2) && !GETBITS(instr, 21, 2)){
        singleDataTransInstr(instr);
    }

    //Multiply
    else if(!GETBITS(instr, 22, 6) && GETBITS(instr, 4, 4) == 0x9){
        multiplyInstr(instr);
    }

    //Data Processing
    else if(!GETBITS(instr, 26, 2)){
        processDataInstr(instr);
    }

    //Invalid instruction
    else{
        fprintf(stderr, "Invalid instruction");
    }
}