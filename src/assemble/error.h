#ifndef ASSEMBLE_ERROR_H_
#define ASSEMBLE_ERROR_H_

typedef enum {
    ERROR_EMPTY = 10,
    ERROR_EXPECTED_INSTRUCTION,
    ERROR_TOO_SHORT,
    ERROR_TOO_LONG,
    ERROR_INVALID_INSTRUCTION,
    ERROR_INVALID_LABEL,
    ERROR_EXPECTED_LABEL_OR_PURE_CONSTANT,
    ERROR_EXPECTED_4_DIVISIBLE,
    ERROR_INVALID_BRANCH,
    ERROR_EXPECTED_REGISTER_OR_HASH_CONSTANT,
    ERROR_INVALID_REGISTER
} ErrorCodes;

typedef enum {
    STAGE_NONE = 10,
    STAGE_DISPATCH,
    STAGE_BRANCH,
    STAGE_SHIFT,
    STAGE_MULTIPLY
} ProcessingStage;

ErrorCodes error_code = ERROR_EMPTY;
ProcessingStage processing_stage;

void SetErrorCode(ProcessingStage stage, ErrorCodes new_error_code);

void ReportError(int line_num, char* file_name, char* line_contents);

#endif /* ASSEMBLE_ERROR_H_ */
