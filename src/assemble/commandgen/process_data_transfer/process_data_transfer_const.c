#include "../common_defs.h"
#include "../../tokenizer.h"
#include "process_data_transfer_const.h"
#include "process_data_transfer_common.h"
#include "../process_data_processing/process_data_processing_common.h"
#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    long long value = TokenConstantValue(VectorGet(tokens, 2));
    if(value <= 0xFF && value >= 0) {
        return LayoutProcConst(
            output,
            offset,
            TokenInstructionConditionType(VectorGet(tokens, 0)),
            0xD,
            0,
            TokenRegisterNumber(VectorGet(tokens, 1)),
            0,
            value
        );
    }
    if(VectorSize(output) < instructions_num) {
        VectorResize(output, instructions_num);
    }
    long long data_offset = VectorSize(output);
    VectorPushBack(output, value);
    return LayoutTransferCommonOffset(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        1,
        1,
        15,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        (data_offset - 2 - offset) * 4
    );
}