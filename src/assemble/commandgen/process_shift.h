/**
 * @file process_shift.h
 * @author Bartłomiej Cieślar
 * @brief shift instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_

#include <stddata.h>
<<<<<<< HEAD

/**
 * @brief Processes shift instructions
 * 
 * The shift instruction must follow one of the following formats:
 *     - <shiftname><cond> Rn, #<expression> - shifts the value of the Rn by the constant amount if
 *       the condition is met (example lsl r4 #21)
 *     - <shiftname><cond> Rn, Rs - shifts the value of the Rn by the amount in Rs if the condition
 *       is met (example ror r2, r7)
 * Note that the shift names are {asr, lsl, lsr, ror}.
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 * @note All registers in those instructions can only be from r0 to r12
 * @note The constant shift cannot exceed 31 and must be non-negative
 */
bool ProcessShift(
    Map symbols, 
    List tokens, 
    Vector output, 
=======
#include <stdbool.h>

bool LayoutShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    int offset, 
    int instructions_num
);

<<<<<<< HEAD
=======
bool LayoutShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
);
>>>>>>> assemble_tokenizer_commongen_using_decision_tree

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_ */
