#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "stddata.h"

/**
 * @brief Given a vector of integers @p program, writes the binary value of these integers to the file of @p filename .
 * @warning asserts that the path to filename exists.
 */
void writeBinary(Vector program, char *filename);

/**
 * @brief Reads each line of @p filename and appends it to @p textLines if the line is in the text section and @p dataLines if the line is in the data section.
 * Recursively descends into any .include statements and reads the lines in order.
 * @warning asserts that the filename exists.
 */
void readFileLines(char *filename, List textLines, List dataLines);

/**
 * @brief Takes the text assembly lines of @p lines and tokenizes each line. At each line, @p totalInstructions is incremented if an instruction was produced.
 * @p symboltable will have any label references added to it in the correct instruction line number.
 * @warning asserts that the filename exists.
 */
List tokenize(List lines, Map symbolTable, int *totalInstructions, Vector dataVector);

/**
 * @brief Takes the text assembly lines of @p lines and tokenizes each line. At each line, @p totalInstructions is incremented if an instruction was produced.
 * @p symboltable will have any label references added to it in the correct instruction line number.
 * @warning asserts that the filename exists.
 */
Vector tokensToBinary(Map symbolTable, List listOfTokens, Vector dataVector, int totalInstructions);

#endif