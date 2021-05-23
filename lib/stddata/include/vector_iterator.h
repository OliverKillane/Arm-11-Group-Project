/**
 * @file vector_iterator.h
 * @author Bartłomiej Cieślar
 * @brief @ref VectorIterator and utilities related to it
 */
#ifndef STDDATA_VECTORITERATOR_H_
#define STDDATA_VECTORITERATOR_H_

#include "vector.h"

/**
 * @brief An iterator for a @ref Vector
 * 
 * The VectorIterator is mainly used for looping over a vector. Example usage in for loops:
 * @code
 * for(VectorIterator iter = VectorBegin(vector); VectorIteratorLess(iter, VectorEnd(vector)); VectorIteratorIncr(&iter)) {
 *     printf("%s\n", (char*)VectorIteratorGet(iter));
 * }
 * @endcode
 * 
 * @note Most of the interface functions require only the value of an iterator to be passed, except
 *       for the ones modifying it ( @ref VectorIteratorIncr and @ref VectorIteratorDecr )
 * @note Most of the time it will be used in combination with the VECTORFOR macro
 * @warning Changing the internal variables manually outside of the interface functions will result
 *          in an undefined behaviour.
 * @warning Attempting to use an uninitialized VectorIterator will result in an undefined behaviour
 */
typedef struct {
    Vector vector;
    int itemNum;
} VectorIterator;

/**
 * @brief A macro for looping over a vector
 * 
 * This macro creates a for loop header using iterators to iterate over a vector.
 * Example usage:
 * @code
 * VECTORFOR(vector, iter) {
 *     printf("%s\n", (char*)VectorIteratorGet(iter));
 * }
 * @endcode
 * 
 * @param vector the vector to be iterated over
 * @param iter the name of the iterator that will index the vector
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
#define VECTORFOR(vector, iter)\
    for(VectorIterator iter = VectorBegin(vector);\
        VectorIteratorLess(iter, VectorEnd(vector));\
        VectorIteratorIncr(&iter))

/**
 * @brief Returns an iterator at the beginning of the vector
 * 
 * @param vector The vector to get the beginning iterator to
 * @return An iterator pointing at the first item of the @p vector
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
VectorIterator VectorBegin(Vector vector);

/**
 * @brief Returns an iterator at the end of the vector
 * 
 * @param vector The vector to get the end iterator to
 * @return An iterator pointing at the item behind the last item of the @p vector
 * @warning @p vector not being a valid allocated @ref Vector results in an undefined behaviour
 */
VectorIterator VectorEnd(Vector vector);

/**
 * @brief Checks if the first iterator points to a smaller index than the second
 * 
 * @return @b true if the first iterator points before the second, otherwise @b false
 * @warning the two iterators not pointing at the same vector will result in an undefined behaviour
 */
bool VectorIteratorLess(VectorIterator a, VectorIterator b);

/**
 * @brief Compares two iterators
 * 
 * @return -1 if the first iterator points to an item before the second iterator
 *         0 if the two iterators point to the same item
 *         1 if the second iterator points to an item before the first iterator
 * @warning the two iterators not pointing at the same vector will result in an undefined behaviour
 */
int VectorIteratorCompare(VectorIterator a, VectorIterator b);

/**
 * @brief Moves the iterator to the next item in the vector
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the vector will result in an
 *          undefined behaviour
 */
void VectorIteratorIncr(VectorIterator *iter);

/**
 * @brief Moves the iterator to the previous item in the vector
 * 
 * @param iter the pointer to the iterator to be incremented
 * @warning trying to increment an iterator pointing at the end of the vector will result in an
 *          undefined behaviour
 */
void VectorIteratorDecr(VectorIterator *iter);

/**
 * @brief Returns an item the iterator is pointing to
 * 
 * @param iter the iterator to dereference
 * @returns the item the iterator is pointing at
 */
void* VectorIteratorGet(VectorIterator iter);

/**
 * @brief Sets an item the iterator is pointing to
 * 
 * @param iter the iterator for which to set the item that it is pointing at
 * @param new_item the new value for the item
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 */
void VectorIteratorSet(VectorIterator iter, void* new_item);

#endif /* STDDATA_VECTORITERATOR_H_ */