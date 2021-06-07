#include "process_expression.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdio.h>

bool ProcessExpression(Map restrict symbols, Vector tokens) {
    Vector new_tokens = NewEmptyVector();
    VECTORFOR(tokens, iter) {
        if(TokenType(VectorIteratorGet(iter)) != TOKEN_LABEL) {
            VectorPushBack(new_tokens, VectorIteratorGet(iter));
            continue;
        }
        if(!MapQuery(symbols, TokenLabel(VectorIteratorGet(iter)))) {
            DeleteVector(new_tokens);
            return true;
        }
        long long address = (long long)MapGet(symbols, TokenLabel(VectorIteratorGet(iter))) * 4;
        DeleteToken(VectorIteratorGet(iter));
        VectorIterator next = iter;
        VectorIteratorIncr(&next);
        VectorIterator next2 = next;
        VectorIteratorIncr(&next2);
        if(!VectorIteratorLess(next, VectorEnd(tokens)) 
           || TokenType(VectorIteratorGet(next)) != TOKEN_SIGN
           || !VectorIteratorLess(next2, VectorEnd(tokens))
           || TokenType(VectorIteratorGet(next2)) != TOKEN_CONSTANT
           || TokenConstantType(VectorIteratorGet(next2)) != CONST_PURE) {
            VectorPushBack(new_tokens, NewConstantToken(CONST_ANY, address));
            continue;
        }
        address += TokenIsPlus(VectorIteratorGet(next)) ? 
                TokenConstantValue(VectorIteratorGet(next2)) : 
                -TokenConstantValue(VectorIteratorGet(next2));

        VectorPushBack(new_tokens, NewConstantToken(CONST_ANY, address));
        
        DeleteToken(VectorIteratorGet(next));
        DeleteToken(VectorIteratorGet(next2));
        iter = next2;
    }

    /* vector in-place swap */
    VectorRepr tmp = *tokens;
    *tokens = *new_tokens;
    *new_tokens = tmp;
    DeleteVector(new_tokens);
}