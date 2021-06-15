#include <stddata.h>
#include <stdio.h>
#include <ctype.h>
#include "error.h"

#define RED "\e[31m"
#define WHITE "\e[37m"


/*  
  improvement note: this code is merely a fill in:
  currently to declare en error:
    if function, setErrorCode, return true
    then once true is received, it calls reportError
    report error immediately exits, but always on 1

    to replace:
     if an error, call (error, line_num, file_name, line_contents, error_code)
     it immediately exits.
*/

ErrorCodes error_code = ERROR_EMPTY;

void SetErrorCode(ErrorCodes new_error_code) {
    assert(error_code == ERROR_EMPTY);
    error_code = new_error_code;
}

void ReportError(int line_num, char* file_name, char* line_contents) {

        /* error code is in error_code global var */
    if (error_code != ERROR_EMPTY) {

        /* if error code not empty,. print line information */
        printf("%s:%d: %s\n" RED "error: " WHITE, file_name, line_num, line_contents);
        
        /* there is an error which requires printing */
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
        }

        /* print newline and reset error code */
        printf("\n");
        error_code = ERROR_EMPTY;
    }
}