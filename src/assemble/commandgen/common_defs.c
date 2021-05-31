#include "common_defs.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdarg.h>

Map data_proc_opcodes;
Map shift_codes;

/* Helper Functions */
void InitDataProcOpcodes() {
    data_proc_opcodes = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(data_proc_opcodes, INSTR_AND, 0b0000);
    MapSet(data_proc_opcodes, INSTR_EOR, 0b0001);
    MapSet(data_proc_opcodes, INSTR_SUB, 0b0010);
    MapSet(data_proc_opcodes, INSTR_RSB, 0b0011);
    MapSet(data_proc_opcodes, INSTR_ADD, 0b0100);
    MapSet(data_proc_opcodes, INSTR_ORR, 0b1100);
    MapSet(data_proc_opcodes, INSTR_MOV, 0b1101);
    MapSet(data_proc_opcodes, INSTR_TST, 0b1000);
    MapSet(data_proc_opcodes, INSTR_TEQ, 0b1001);
    MapSet(data_proc_opcodes, INSTR_CMP, 0b1010);
}

void InitShiftCodes() {
    shift_codes = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(shift_codes, INSTR_LSL, 0b00);
    MapSet(shift_codes, INSTR_LSR, 0b01);
    MapSet(shift_codes, INSTR_ASR, 0b10);
    MapSet(shift_codes, INSTR_ROR, 0b11);
}

/* Interface Definitions */
void InitFunctionGen() {
    InitDataProcOpcodes();
    InitShiftCodes();
    InitInstructionLayouts();
}

void FinishFunctionGen() {
    FinishInstructionLayouts();
    DeleteMap(data_proc_opcodes);
    DeleteMap(shift_codes);
}

void SetInstruction(Vector restrict output, int instruction, int offset) {
    if(VectorSize(output) <= offset) {
        VectorResize(output, offset + 1);
    }
    VectorSet(output, offset, instruction);
}

unsigned int FillInstruction(int nfields, ...) {
    va_list args;
    va_start(args, nfields);

    unsigned int instruction = 0;
    for(int i = 0; i < nfields; i++) {
        unsigned int value = va_arg(args, unsigned int);
        unsigned int shift = va_arg(args, unsigned int);
        instruction |= value << shift;
    }

    va_end(args);
    
    return instruction;
}