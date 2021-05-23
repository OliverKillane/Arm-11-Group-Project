/**
 * @file set_iterator.h
 * @author Bartłomiej Cieślar
 * @brief @ref SetIterator and utilities related to it
 */
#ifndef STDDATA_SET_ITERATOR_H_
#define STDDATA_SET_ITERATOR_H_

#include <assert.h>
#include "set.h"

/**
 * @brief An iterator for a @ref Set
 * 
 * The SetIterator is mainly used for looping over a set. Example usage in for loops:
 * @code
 * for(SetIterator iter = SetBegin(set); SetIteratorLess(iter, SetEnd(set)); SetIteratorIncr(&iter)) {
 *     printf("%s\n", (char*)SetIteratorGet(iter));
 * }
 * @endcode
 * 
 * @note Most of the interface functions require only the value of an iterator to be passed, except
 *       for the ones modifying it ( @ref SetIteratorIncr and @ref SetIteratorDecr )
 * @note Most of the time it will be used in combination with the SETFOR macro
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 * @warning Attempting to use an uninitialized SetIterator will result in an undefined behaviour
 */
typedef struct {
    Set set;
    int index;
} SetIterator;

/**
 * @brief A macro for looping over a set
 * 
 * This macro creates a for loop header using iterators to iterate over a set.
 * Example usage:
 * @code
 * SETFOR(set, iter) {
 *     printf("%s\n", (char*)SetIteratorGet(iter));
 * }
 * @endcode
 * 
 * @param set the set to be iterated over
 * @param iter the name of the iterator that will index the set
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
#define SETFOR(set, iter) \
    for(SetIterator iter = SetBegin(set); \
        SetIteratorLess(iter, SetEnd(set)); \
        SetIteratorIncr(&iter))

/**
 * @brief Returns an iterator at the beginning of the set
 * 
 * @param set The set to get the beginning iterator to
 * @return An iterator pointing at the first item of the @p set
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
SetIterator SetBegin(Set set);

/**
 * @brief Returns an iterator at the end of the set
 * 
 * @param set The set to get the end iterator to
 * @return An iterator pointing at the item behind the last item of the @p set
 * @warning @p set not being a valid allocated @ref Set results in an undefined behaviour
 */
SetIterator SetEnd(Set set);

/**
 * @brief Checks if the first iterator points before the second
 * 
 * @return @b true if the first iterator points before the second, otherwise @b false
 * @warning the two iterators not pointing at the same set will result in an undefined behaviour
 */
bool SetIteratorLess(SetIterator a, SetIterator b);

/**
 * @brief Compares two iterators
 * 
 * @return -1 if the first iterator points to an item before the second iterator
 *         0 if the two iterators point to the same item
 *         1 if the second iterator points to an item before the first iterator
 * @warning the two iterators not pointing at the same set will result in an undefined behaviour
 */
int SetIteratorCompare(SetIterator a, SetIterator b);

/**
 * @brief Moves the iterator to the next item in the set
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the set will result in an
 *          undefined behaviour
 */
void SetIteratorIncr(SetIterator *iter);

/**
 * @brief Moves the iterator to the previous item in the set
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the set will result in an
 *          undefined behaviour
 */
void SetIteratorDecr(SetIterator *iter);

/**
 * @brief Returns an item the iterator is pointing to
 * 
 * @param iter the iterator to dereference
 * @returns the item the iterator is pointing at
 */
void* SetIteratorGet(SetIterator iter);


#endif /* STDDATA_SET_ITERATOR_H_ */