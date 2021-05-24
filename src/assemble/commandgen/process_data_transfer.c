#include "process_data_transfer.h"
#include <stddata.h>
#include "common_defs.h"

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    return GetExpressionValue(
        dummy, ListPopFront(tokens), false, true
    ) << 3;
}

static inline unsigned int ProcessRegisterShift(List restrict tokens) {
    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_s = GetRegisterNum(ListPopFront(tokens));
    
    return (reg_s << 4) | 1;
}

static inline unsigned int ProcessRegister(List restrict tokens) {
    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_m = GetRegisterNum(ListPopFront(tokens));
    assert(reg_m <= 12);
    
    unsigned int shift = 0;
    if(ListSize(tokens) > 0) {
        assert(ListSize(tokens) == 2);
        assert(MapQuery(shift_codes, ListFront(tokens)));
        const unsigned int shift_code = MapGet(shift_codes, ListPopFront(tokens));
        
        shift |= shift_code << 1;

        shift |= IsImmediate(ListFront(tokens), false, true) ?
            ProcessImmediateShift(tokens) : ProcessRegisterShift(tokens);
    }

    int operand2 = 0;
    operand2 |= reg_m;
    operand2 |= shift << 4;

    return operand2;
}

unsigned int ProcessLoadMov(unsigned int condition, unsigned int reg_d, unsigned int expression) {
    unsigned int instruction = 0;
    instruction |= condition << 28;
    instruction |= 0x3A << 20;
    instruction |= reg_d << 12;
    instruction |= expression;
    return instruction;
}

void ProcessLoadBig(
    unsigned int condition,
    unsigned int reg_d, 
    unsigned int expression, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(VectorSize(output) < instructions_num) {
        VectorResize(output, instructions_num);
    }
    unsigned int data_offset = VectorSize(output) * 4 - 8 - offset * 4;
    assert(data_offset < (1<<12));
    VectorPushBack(output, expression);

    unsigned int instruction = 0;
    instruction |= condition << 28;
    instruction |= 0x59 << 20;
    instruction |= 0xF << 16;
    instruction |= reg_d << 12;
    instruction |= data_offset;

    SetInstruction(output, instruction, offset);
}

void ProcessLoadConst(
    unsigned int condition, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_d = GetRegisterNum(ListPopFront(tokens));
    unsigned int expression = GetExpressionValue(dummy, ListPopFront(tokens), false, false);
    if(expression < (1<<12)) {
        SetInstruction(output, ProcessLoadMov(condition, reg_d, expression), offset);
    } else {
        ProcessLoadBig(condition, reg_d, expression, output, offset, instructions_num);
    }
}

void ProcessDataTransfer(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(ListSize(tokens) >= 3);
    unsigned int condition;
    char func_base[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(ListPopFront(tokens), func_base, &condition);

    unsigned int load_flag = StringEq(func_base, "ldr");
    if(load_flag && IsImmediate(ListBack(tokens), false, false)) {
        ProcessLoadConst(condition, tokens, output, offset, instructions_num);
        return;
    }

    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_d = GetRegisterNum(ListPopFront(tokens));
    assert(reg_d <= 12);

    assert(StringEq(ListPopFront(tokens), "["));
    assert(ListSize(tokens) >= 2);

    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_n = GetRegisterNum(ListPopFront(tokens));

    unsigned int pre_flag;
    if(StringEq(ListBack(tokens), "]")) {
        pre_flag = 1;
        ListPopBack(tokens);
    } else {
        pre_flag = 0;
        assert(StringEq(ListFront(tokens), "]"));
        ListPopFront(tokens);
    }

    unsigned int operand = 0;
    unsigned int up_flag = 1;
    unsigned int immediate_flag = 0;

    if(!ListEmpty(tokens)) {
        if(IsImmediate(ListFront(tokens), false, true)) {
            long long value = GetExpressionValue(dummy, ListPopFront(tokens), false, true);
            assert(ListEmpty(tokens));
            up_flag = value >= 0;
            assert(value < (1<<12) && value > -(1<<12));
            operand = abs(value);
            immediate_flag = 0;
        } else {
            if(((char*)ListFront(tokens))[0] == '+' || ((char*)ListFront(tokens))[0] == '-') {
                up_flag = ((char*)ListFront(tokens))[0] == '+';
                ListSet(tokens, 0, ((char*)ListFront(tokens)) + 1);
            } else {
                up_flag = 1;
            }
            operand = ProcessRegister(tokens);
            immediate_flag = 1;
        }
    }

    int instruction = 0;
    instruction |= condition << 28;
    instruction |= 1 << 26;
    instruction |= immediate_flag << 25;
    instruction |= pre_flag << 24;
    instruction |= up_flag << 23;
    instruction |= load_flag << 20;
    instruction |= reg_n << 16;
    instruction |= reg_d << 12;
    instruction |= operand;

    SetInstruction(output, instruction, offset);
}