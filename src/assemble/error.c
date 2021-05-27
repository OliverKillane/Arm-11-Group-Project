#include <stddata.h>
#include "error.h"

#define RED "\0x1b[38;5;31m"
#define WHITE "0x1b[38;5;37m"

void SetErrorCode(ProcessingStage stage, ErrorCodes new_error_code) {
    assert(error_code == ERROR_EMPTY);
    error_code = new_error_code;
    processing_stage = stage;
}

Map ErrorMessagesMap() {
    Map error_messages = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);

    MapSet(error_messages, ERROR_EXPECTED_INSTRUCTION, "expected instruction token");
    MapSet(error_messages, ERROR_TOO_SHORT, "expected more tokens");
    MapSet(error_messages, ERROR_TOO_LONG, "expected less tokens");
    MapSet(error_messages, ERROR_INVALID_INSTRUCTION, "invalid instruction code");
    MapSet(error_messages, ERROR_INVALID_LABEL, "label not found");
    MapSet(error_messages, ERROR_EXPECTED_LABEL_OR_PURE_CONSTANT, 
            "expected label or prefixless constant");
    MapSet(error_messages, ERROR_EXPECTED_4_DIVISIBLE, "expected a constant divisible by 4");
    MapSet(error_messages, ERROR_CONST_OOB, "constant out of bounds");
    MapSet(error_messages, ERROR_EXPECTED_REGISTER_OR_HASH_CONSTANT, 
            "expected register or a constant preceded by a hash");
    MapSet(error_messages, ERROR_INVALID_REGISTER, "invalid register");
    MapSet(error_messages, ERROR_EXPECTED_REGISTER, "expected a register");
    MapSet(error_messages, ERROR_OFFSET_TOO_FAR, "instruciton offset too big to store");
    MapSet(error_messages, ERROR_EXPECTED_EQUALS_CONSTANT_OR_BRACE, 
            "expected a constant preceded by an equals sign or an open square bracket");
    MapSet(error_messages, ERROR_EXPECTED_CLOSED_BRACE, "expected closed bracket");
    MapSet(error_messages, ERROR_EXPECTED_HASH_CONSTANT, "expected a constant preceded by a hash");
    MapSet(error_messages, ERROR_SHIFT_OOB, "shift out of bounds");

    return error_messages;
}

Map StagesNamesMap() {
    Map stages_names = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);

    MapSet(stages_names, STAGE_NONE, "unspecified");
    MapSet(stages_names, STAGE_DISPATCH, "instruction processing dispatch");
    MapSet(stages_names, STAGE_BRANCH, "branch instruction generation");
    MapSet(stages_names, STAGE_MULTIPLY, "multiply instruction generation");
    MapSet(stages_names, STAGE_DATA_TRANSFER, "data transfer instruction generation");
    MapSet(stages_names, STAGE_SHIFTED_REGISTER, "shifted register data source generation");

    return stages_names;
}

void ReportError(int line_num, char* file_name, char* line_contents) {
    if(error_code == ERROR_EMPTY) {
        return;
    }
    Map error_messages = ErrorMessagesMap();
    Map stages_names = StagesNamesMap();

    printf(
        "%s:%d: %s\n" RED "error while doing %s:" WHITE "%s\n", 
        file_name, 
        line_num, 
        line_contents,
        MapGet(stages_names, processing_stage),
        MapGet(error_messages, error_code)
    );

    DeleteMap(error_messages);
    DeleteMap(stages_names);
    error_code = ERROR_EMPTY;
}