/**
 * @file process_data_transfer.h
 * @author Bartłomiej Cieślar
 * @brief data transfer instructions processing
 */
<<<<<<< HEAD
=======

>>>>>>> assemble_tokenizer_commongen_using_decision_tree
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_

#include <stddata.h>
<<<<<<< HEAD

/**
 * @brief Processes data transfer instructions
 *
 * The data transfer instruction must be in one of the following formats:
 *     - ldr<cond> Rd, =<expression> - places the value of the expression in Rd if the condition is met
 *     - <ldr/str><cond> Rd, [Rn] - places the value of Rd under an address Rn or stores the value at the
 *                                  address Rn at the register Rd
 *     - <ldr/str><cond> Rd, [Rn, <Operand>] - places the value of Rd under an address Rn + <Operand2> or 
 *                                             stores the value at the address Rn + <Operand2> at the register Rd
 *                                              
 *     - <ldr/str><cond> Rd, [Rn], <Operand> - places the value of Rd under an address Rn or stores the value at the
 *                                  address Rn at the register Rd and increments Rn by <Operand2>
 * 
 * Where <Operand2> must follow one of the following formats:
 *     - #<expression> - a constant value (example #0xFF)
 *     - <+/-> Rm - <+/-> the value of Rm (example -r11)
 *     - <+/-> Rm, <shiftname> #<expression> - <+/-> the value of Rm shifted by a constant amount (example r0, ror #5)
 *     - <+/-> Rm, <shiftname> Rs - <+/-> the value of Rm shifted by the amount in Rs (example +r8, asr r1)
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 * @note <Operand2> with a constant value represented in one's complement must fit in 13 bits
 * @note The constant shift cannot exceed 31 and must be non-negative
 * @note Rs and Rd can only be from r0 to R12
 * @note If the unsigned =<expression> is bigger than 255 then the load instruction cannot be more than 4104 bytes from the data section
 *       of the executable
 */
bool ProcessDataTransfer(
    Map symbols, 
    List tokens, 
=======
#include <stdbool.h>

bool LayoutTransferSet(
    Map symbols, 
    Vector tokens, 
    Vector output,
    int offset, 
    int instructions_num
);

bool LayoutTransferConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferShiftReg(
    Map symbols, 
    Vector tokens, 
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_ */
