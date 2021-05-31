/**
 * @file process_data_processing.h
 * @author Bartłomiej Cieślar
 * @brief data processing instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_

#include <stddata.h>

/**
 * @brief Processes data processing instructions
 * 
 * The data processing instruction must follow one of the following formats:
 *     - <compute_instruction><cond> Rd, Rn, <Operand2> - computes the result of applying the compute instruction
 *       to Rn and <Operand2> and places it in Rd if the condition holds (example: addal r2, r4, r3)
 *     - mov<cond> Rd, <Operand2> - moves the value of <Operand2> and places it in Rd if the condition
 *       holds (example: movge r1, #56)
 *     - <test_instruction><cond> Rn, <Operand2> - tests the values Rn and <Operand2> and sets CPSR flags
 *       accordingly if the condition holds (example teqle r2, r12)
 * Where <Operand2> must follow one of the following formats:
 *     - #<expression> - a constant value (example #0xFF)
 *     - Rm - a value of a register (example r11)
 *     - Rm, <shiftname> #<expression> - a value of Rm shifted by a constant amount (example r0, ror #5)
 *     - Rm, <shiftname> Rs - a value of Rm shifted by the amount in Rs (example r8, asr r1)
 * Note that the compute instructions are {and, eor, sub, rsb, add, orr}, test instructions are 
 * {tst, teq, cmp} and shift names are {asr, lsl, lsr, ror}.
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 * @note All registers in those instructions can only be from r0 to r12
 * @note The constant shift cannot exceed 31 and must be non-negative
 * @note <Operand2> with a constant value must be representable by a single-byte value rotated an even number of times 
 *       (within 32 bits) and must be non-negative
 */
bool ProcessDataProcessing(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_ */
