/**
 * @file process_branch.h
 * @author Bartłomiej Cieślar
 * @brief branch instruction processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_

#include <stddata.h>
<<<<<<< HEAD

/**
 * @brief Processses a branch instruction
 * 
 * The branch instruction must follow one of the following formats:
 *     - b<cond> <expression> - jumps to the instruction at the specified address if the condition
 *       holds (examples: beq 0x4122 or beq 1234)
 *     - b<cond> <label> - jumps to the instruction at the specified label if the condition
 *       holds (example: ble forloop)
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 * @note in the format b<cond> <expression> the value of the expression must be divisible by 4 and non-negative
 * @note the jump cannot be performed to the destination more than 2^26 from the address 8 bytes ahead of the branch instruction
 */
bool ProcessBranch(
    Map symbols, 
    List tokens, 
    Vector output, 
=======
#include <stdbool.h>

bool LayoutBranchLabel(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
);

bool LayoutBranchConstant(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_ */
