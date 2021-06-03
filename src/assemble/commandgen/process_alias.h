#ifndef ASSEMBLE_COMMANDGEN_PROCESS_ALIAS_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_ALIAS_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutRet(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutHalt(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutPush(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutPop(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_ALIAS_H_ */
