#ifndef STDDATA_MAP_UTILS_H_
#define STDDATA_MAP_UTILS_H_

#include <stdbool.h>

/*
 * Hash function for strings
 */
unsigned long long StringHash(void*);

/*
 * Equality function for strings
 */
bool StringEq(void*, void*);

/*
 * Hash function for ints in pointers
 */
unsigned long long IntPtrHash(void*);

/*
 * Equality function for ints in pointers
 */
bool IntPtrEq(void*, void*);

/*
 * Hash function for ints inside void*
 */
unsigned long long IntHash(void*);

/*
 * Equality function for ints inside void*
 */
bool IntEq(void*, void*);

#endif /* STDDATA_MAP_UTILS_H_ */