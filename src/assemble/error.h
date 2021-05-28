/**
 * @file error.h
 * @author your name (you@domain.com)
 * @brief Definitions regarding  error messages for assembler
 */
#ifndef ASSEMBLE_ERROR_H_
#define ASSEMBLE_ERROR_H_

/**
 * @brief Describes the types of errors that can occur
 */
typedef enum {
    ERROR_EMPTY = 10,
    ERROR_EXPECTED_INSTRUCTION,
    ERROR_TOO_SHORT,
    ERROR_TOO_LONG,
    ERROR_INVALID_INSTRUCTION,
    ERROR_INVALID_LABEL,
    ERROR_EXPECTED_LABEL_OR_PURE_CONSTANT,
    ERROR_EXPECTED_4_DIVISIBLE,
    ERROR_CONST_OOB,
    ERROR_EXPECTED_REGISTER_OR_HASH_CONSTANT,
    ERROR_INVALID_REGISTER,
    ERROR_EXPECTED_REGISTER,
    ERROR_OFFSET_TOO_FAR,
    ERROR_EXPECTED_EQUALS_CONSTANT_OR_BRACE,
    ERROR_EXPECTED_CLOSED_BRACE,
    ERROR_EXPECTED_HASH_CONSTANT,
    ERROR_SHIFT_OOB,
    ERROR_EXPECTED_CONDITIONLESS_SHIFT
} ErrorCodes;

/**
 * @brief Describes the stages of assembling on which the errors can occur
 */
typedef enum {
    STAGE_NONE = 10,
    STAGE_DISPATCH,
    STAGE_BRANCH,
    STAGE_MULTIPLY,
    STAGE_DATA_TRANSFER,
    STAGE_SHIFTED_REGISTER,
    STAGE_DATA_PROCESSING
} ProcessingStage;

ErrorCodes error_code = ERROR_EMPTY;
ProcessingStage processing_stage = STAGE_NONE;

/**
 * @brief Sets the error data
 * 
 * @warning Can be used only once before reporting it with @ref ReportError
 */
void SetErrorCode(ProcessingStage stage, ErrorCodes new_error_code);

/**
 * @brief Reports an error set with @ref SetErrorCode and allows for setting another error
 * 
 * @note Calling this function several times without calling @ref SetErrorCode inbetween only
 *       prints one error message
 */
void ReportError(int line_num, char* file_name, char* line_contents);

#endif /* ASSEMBLE_ERROR_H_ */
