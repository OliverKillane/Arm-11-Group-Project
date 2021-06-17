#include <stddata.h>
#include <stdio.h>
#include <ctype.h>
#include "error.h"

/* printing colours */
#define RED "\033[31m"
#define WHITE "\033[37m"

/* global error_code can be set by subroutines */
ErrorCodes error_code = ERROR_EMPTY;

void SetErrorCode(ErrorCodes new_error_code) {

    /* assert that there was no previous error and set the error code */
    assert(error_code == ERROR_EMPTY);
    error_code = new_error_code;
}

void ReportError(int line_num, char* file_name, char* line_contents) {
    /* error code is in error_code global var */
    if (error_code != ERROR_EMPTY) {

        /* if error code not empty,. print line information */
        printf("%s:%d: %s\n" RED "error: " WHITE, file_name, line_num, line_contents);
        
        /* there is an error which requires printing, print error string */
        switch(error_code) {
            case ERROR_INVALID_PATTERN:
                printf("Instruction pattern not found");
                break;
            case ERROR_LABEL_NOT_FOUND:
                printf("Label not found");
                break;
            case ERROR_INVALID_REGISTER:
                printf("Invalid register used");
                break;
            case ERROR_CONSTANT_OOB:
                printf("Constant out of bounds");
                break;
            case ERROR_SAME_REGISTERS:
                printf("Some registers that shouldn't be the same are the same");
                break;
            case ERROR_OFFSET_OOB:
                printf("Offset to the instruction out of bounds");
                break;
            case ERROR_CONDITIONAL_SHIFT:
                printf("The shift specifier should not be conditional");
                break;
            default:
                break;
        }

        /* print newline */
        printf("\n");

        /* exit on the error code */
        exit(error_code);
    }
}