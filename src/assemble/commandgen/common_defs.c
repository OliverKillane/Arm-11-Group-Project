#include "common_defs.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdarg.h>

Map data_proc_opcodes;
Map shift_codes;
Map label_masks;

/* Helper Functions */
void InitDataProcOpcodes() {
    data_proc_opcodes = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(data_proc_opcodes, INSTR_AND, 0x0);
    MapSet(data_proc_opcodes, INSTR_EOR, 0x1);
    MapSet(data_proc_opcodes, INSTR_SUB, 0x2);
    MapSet(data_proc_opcodes, INSTR_RSB, 0x3);
    MapSet(data_proc_opcodes, INSTR_ADD, 0x4);
    MapSet(data_proc_opcodes, INSTR_ORR, 0xC);
    MapSet(data_proc_opcodes, INSTR_MOV, 0xD);
    MapSet(data_proc_opcodes, INSTR_TST, 0x8);
    MapSet(data_proc_opcodes, INSTR_TEQ, 0x9);
    MapSet(data_proc_opcodes, INSTR_CMP, 0xA);
}

void InitShiftCodes() {
    shift_codes = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(shift_codes, INSTR_LSL, 0x0);
    MapSet(shift_codes, INSTR_LSR, 0x1);
    MapSet(shift_codes, INSTR_ASR, 0x2);
    MapSet(shift_codes, INSTR_ROR, 0x3);
}

void InitLabelMask() {
    label_masks = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(label_masks, LABEL_FULL,    0xFFFFFFFF);
    MapSet(label_masks, LABEL_FIRST8,  0x000000FF);
    MapSet(label_masks, LABEL_SECOND8, 0x0000FF00);
    MapSet(label_masks, LABEL_THIRD8,  0x00FF0000);
    MapSet(label_masks, LABEL_FOURTH8, 0xFF000000);
}

/* Interface Definitions */
void InitFunctionGen() {
    InitDataProcOpcodes();
    InitShiftCodes();
    InitLabelMask();
    InitInstructionLayouts();
}

void FinishFunctionGen() {
    FinishInstructionLayouts();
    DeleteMap(data_proc_opcodes);
    DeleteMap(shift_codes);
    DeleteMap(label_masks);
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