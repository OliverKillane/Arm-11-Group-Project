/**
 * @file hash_utils.h
 * @author Bartłomiej Cieślar
 * @brief Hash and equality functions for commonly used types for using in @ref Map or @ref Set
 */
#ifndef STDDATA_HASH_UTILS_H_
#define STDDATA_HASH_UTILS_H_

#include <stdbool.h>

/**
 * @brief Hash function for strings for using in @ref Map or @ref Set
 */
unsigned long long StringHash(void*);

/**
 * @brief Equality function for strings for using in @ref Map or @ref Set
 */
bool StringEq(void*, void*);

/**
 * @brief Hash function for integers stored under pointers for using in @ref Map or @ref Set
 */
unsigned long long IntHash(void*);

/**
 * @brief Equality function for integers stored under pointers for using in @ref Map or @ref Set
 */
bool IntEq(void*, void*);

/**
 * @brief Hash function for integer stored inside void* for using in @ref Map or @ref Set
 */
unsigned long long UnsafeIntHash(void*);

/**
 * @brief Equality function for integer stored inside void* for using in @ref Map or @ref Set
 */
bool UnsafeIntEq(void*, void*);

#endif /* STDDATA_HASH_UTILS_H_ */