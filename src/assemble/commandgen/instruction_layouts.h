/**
 * @file instruction_layouts.h
 * @author Bartłomiej Cieślar
 * @brief Common decision trees used throughout all instruction processing functions
 */
#ifndef ASSEMBLE_COMMANDGEN_INSTRUCTION_LAYOUTS_H_
#define ASSEMBLE_COMMANDGEN_INSTRUCTION_LAYOUTS_H_

#include <stddata.h>

/**
 * @brief DecisionTree<Token, bool*(Map, Vector, Vector, int, int)> from the possible instruction layout to the function processing it
 */
extern DecisionTree instruction_layouts;
/**
 * @brief DecisionTree<Token, unsigned int> of possible bracket layouts and what they represent
 */
extern DecisionTree bracket_layouts;

/**
 * @brief Transfers the data from the @param tokens to the @param field
 * 
 * Based on the data paths set in @ref InitInstructionLayouts transfers the data from the tokens to the
 * respective fields, allowing for default values for the fields that do not end up set and allowing for
 * reusing the function. The following field types correspond to the token types that set the data:
 *      - TOKEN_CONSTANT: long long - the constant value
 *      - TOKEN_INSTRUCTION: InstructionType - the instruction type
 *      - TOKEN_REGISTER: unsigned int - the register index
 *      - TOKEN_SIGN: unsigned int - 1 if the token is a plus 0 otherwise
 *      - all other token types are skipped
 * @param tokens The tokens that are the source of data
 * @param n The number of fields proceeding
 * @param field The instruction field to be filled based on the tokens
 */
void ProcessDataLayout(Vector tokens, int n, ...);

/**
 * @brief Sets the decision trees for: instruction layouts for processing dispatch( @ref instruction_layouts ), @ref bracket_layouts and data paths for the @ref ProcessDataLayout
 */
void InitInstructionLayouts();

/**
 * @brief Deallocates all the decision trees for commandgen
 */
void FinishInstructionLayouts();

#endif /* ASSEMBLE_COMMANDGEN_INSTRUCTION_LAYOUTS_H_ */
