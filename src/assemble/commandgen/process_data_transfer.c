
#include "common_defs.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include "process_data_transfer.h"
#include <stddata.h>
#include <stdio.h>

bool LayoutTransferSet(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    unsigned int reg_d = TokenRegisterNumber(VectorGet(tokens, 1));
    unsigned int constant = TokenConstantValue(VectorGet(tokens, 2));
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));

    if(constant < (1<<8)) {
        SetInstruction(text, FillInstruction(
            5,
            cond, 28,
            0x1, 25,
            MapGet(data_proc_opcodes, (void*)INSTR_MOV), 21,
            reg_d, 12,
            constant, 0
        ), offset);
        return false;
    }

    long long data_offset = VectorSize(data) + instructions_num;
    VectorPushBack(data, constant);
    SetInstruction(text, FillInstruction(
        7,
        cond, 28,
        0x1, 26,
        0x3, 23,
        0x1, 20,
        0xF, 16,
        reg_d, 12,
        (data_offset - 2 - offset) * 4, 0
    ), offset);
    
    return false;
}

bool LayoutTransferConst(
    Map restrict symbols, 
    Vector restrict tokens,
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n;
    unsigned int reg_d;
    long long constant = 0;
    ProcessDataLayout(tokens, 4, &type, &reg_n, &reg_d, &constant);

    unsigned int pre = DecisionTreeQuery(bracket_layouts, tokens);
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int load = type == INSTR_LDR;
    SetInstruction(text, FillInstruction(
        8,
        cond, 28,
        0x1, 26,
        pre, 24,
        constant >= 0, 23,
        load, 20,
        reg_n, 16,
        reg_d, 12,
        abs(constant), 0
    ), offset);

    return false;
}

bool LayoutTransferShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n;
    unsigned int reg_d;
    unsigned int reg_m;
    unsigned int up = 1;
    InstructionType shift_name = INSTR_LSL;
    long long shift_value = 0;
    ProcessDataLayout(tokens, 7, &type, &reg_n, &reg_d, &reg_m, &up, &shift_name, &shift_value);

    unsigned int pre = DecisionTreeQuery(bracket_layouts, tokens);
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int load = type == INSTR_LDR;
    SetInstruction(text, FillInstruction(
        10,
        cond, 28,
        0x3, 25,
        pre, 24,
        up, 23,
        load, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        MapGet(shift_codes, (void*)shift_name), 5,
        shift_value, 7
    ), offset);

    return false;
}

bool LayoutTransferShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n;
    unsigned int reg_d;
    unsigned int reg_m;
    unsigned int up = 1;
    InstructionType shift_name;
    unsigned int reg_s;
    ProcessDataLayout(tokens, 7, &type, &reg_n, &reg_d, &reg_m, &up, &shift_name, &reg_s);

    unsigned int pre = DecisionTreeQuery(bracket_layouts, tokens);
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int load = type == INSTR_LDR;
    SetInstruction(text, FillInstruction(
        11,
        cond, 28,
        0x3, 25,
        pre, 24,
        up, 23,
        load, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        0x1, 4,
        MapGet(shift_codes, (void*)shift_name), 5,
        reg_s, 8
    ), offset);

    return false;
}