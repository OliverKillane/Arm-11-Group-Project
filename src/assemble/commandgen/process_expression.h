/**
 * @file process_expression.h
 * @author Bartłomiej Cieślar
 * @brief Expression processing before instruction processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_EXPRESSION_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_EXPRESSION_H_

#include <stddata.h>

/**
 * @brief Converts label expressions into constants of type CONST_ANY in-place
 */
bool ProcessExpression(Map symbols, Vector tokens);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_EXPRESSION_H_ */
