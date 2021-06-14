#include <stddata.h>
#include <stdio.h>
#include <ctype.h>
#include "error.h"

#define RED "\e[31m"
#define WHITE "\e[37m"

ErrorCodes error_code = ERROR_EMPTY;

void SetErrorCode(ErrorCodes new_error_code) {
    assert(error_code == ERROR_EMPTY);
    error_code = new_error_code;
}

Map ErrorMessagesMap() {
    Map error_messages = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(error_messages, ERROR_INVALID_PATTERN, "Instruction pattern not found");
    MapSet(error_messages, ERROR_LABEL_NOT_FOUND, "Label not found");
    MapSet(error_messages, ERROR_INVALID_REGISTER, "Invalid register used");
    MapSet(error_messages, ERROR_CONSTANT_OOB, "Constant out of bounds");
    MapSet(error_messages, ERROR_SAME_REGISTERS, "Some registers that shouldn't be the same are the same");
    MapSet(error_messages, ERROR_OFFSET_OOB, "Offset to the instruction out of bounds");
    MapSet(error_messages, ERROR_CONDITIONAL_SHIFT, "The shift specifier should not be conditional");
    return error_messages;
}

void ReportError(int line_num, char* file_name, char* line_contents) {
    if(error_code == ERROR_EMPTY) {
        return;
    }
    Map error_messages = ErrorMessagesMap();

    while(isspace(*line_contents)) {
        line_contents++;
    }
    printf(
        "%s:%d: %s\n" RED "error: " WHITE "%s\n", 
        file_name, 
        line_num, 
        line_contents,
        MapGet(error_messages, (int)error_code)
    );

    DeleteMap(error_messages);
    error_code = ERROR_EMPTY;
}