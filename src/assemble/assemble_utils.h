#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "stddata.h"

/**
 * @brief Given a vector of integers @p program, writes the binary value of these integers to the file of @p filename .
 * @warning asserts that the path to filename exists.
 */
void writeBinary(Vector program, char *filename);

void readFileLines(char *filename, List textLines, List dataLines);

List tokenize(List lines, Map symbolTable, int *totalInstructions, Vector dataVector);

Vector tokensToBinary(Map symbolTable, List listOfTokens, Vector dataVector, int totalInstructions);

#endif