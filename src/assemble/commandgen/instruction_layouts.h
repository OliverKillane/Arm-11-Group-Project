#ifndef ASSEMBLE_COMMANDGEN_INSTRUCTION_LAYOUTS_H_
#define ASSEMBLE_COMMANDGEN_INSTRUCTION_LAYOUTS_H_

#include <stddata.h>

extern DecisionTree instruction_layouts;
extern DecisionTree bracket_layouts;

void ProcessDataLayout(Vector tokens, int n, ...);

void InitInstructionLayouts();

void FinishInstructionLayouts();

#endif /* ASSEMBLE_COMMANDGEN_INSTRUCTION_LAYOUTS_H_ */
