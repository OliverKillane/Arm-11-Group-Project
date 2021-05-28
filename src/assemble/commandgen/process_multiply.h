/**
 * @file process_shift.h
 * @author Bartłomiej Cieślar
 * @brief multiply instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_

#include <stddata.h>

/**
 * @brief Processes multiply instructions
 * 
 * The multiply instruction must follow one of the following formats:
 *     - mul<cond> Rd Rm Rs - places the result of Rm * Rs in Rd if the condition is met (example: muleq r1 r2 r3)
 *     - mla<cond> Rd, Rm, Rs, Rn - places the result of Rm * Rs + Rn in Rd (example: mlalt r1, r2, r3, r4)
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 * @note All registers in those instructions can only be from r0 to r12
 */
bool ProcessMultiply(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_ */
