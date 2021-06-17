/**
 * @file error.h
 * @author Bartlomeij
 * @brief Definitions regarding  error messages for assembler
 */
#ifndef ASSEMBLE_ERROR_H_
#define ASSEMBLE_ERROR_H_

/**
 * @brief Describes the types of errors that can occur
 */
typedef enum {
    ERROR_EMPTY,
    ERROR_INVALID_PATTERN,
    ERROR_LABEL_NOT_FOUND,
    ERROR_INVALID_REGISTER,
    ERROR_CONSTANT_OOB,
    ERROR_SAME_REGISTERS,
    ERROR_OFFSET_OOB,
    ERROR_CONDITIONAL_SHIFT
} ErrorCodes;

extern ErrorCodes error_code;

/**
 * @brief Sets the error data
 * 
 * @warning Can be used only once before reporting it with @ref ReportError
 */
void SetErrorCode(ErrorCodes new_error_code);

/**
 * @brief Reports an error set with @ref SetErrorCode and allows for setting another error
 * 
 * @note Calling this function several times without calling @ref SetErrorCode inbetween only
 *       prints one error message
 */
void ReportError(int line_num, char* file_name, char* line_contents);

#endif /* ASSEMBLE_ERROR_H_ */
