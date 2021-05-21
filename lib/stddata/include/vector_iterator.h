#ifndef STDDATA_VECTORITERATOR_H_
#define STDDATA_VECTORITERATOR_H_

#include "vector.h"

typedef struct {
    Vector vector;
    int itemNum;
} VectorIterator;

#define VECTORFOR(vector, iter)\
    for(VectorIterator iter = VectorBegin(vector);\
        VectorIteratorLess(iter, VectorEnd(vector));\
        VectorIteratorIncr(&iter))

/*
 * Returns an iterator to the beginning of the vector
 */
VectorIterator VectorBegin(Vector vector);

/*
 * Returns an iterator to the end of the vector
 */
VectorIterator VectorEnd(Vector vector);

/*
 * Checks if the first iterator points to a spot before the second
 */
bool VectorIteratorLess(VectorIterator a, VectorIterator b);

/*
 * Comparator function for iterators
 */
int VectorIteratorCompare(VectorIterator a, VectorIterator b);

/*
 * Increments the iterator
 */
void VectorIteratorIncr(VectorIterator *iter);

/*
 * Decrements the iterator
 */
void VectorIteratorDecr(VectorIterator *iter);

/*
 * Gets an item the iterator is pointing to
 */
void* VectorIteratorGet(VectorIterator iter);

/*
 * Sets an item the iterator is pointing to
 */
void VectorIteratorSet(VectorIterator iter, void* newItem);

#endif /* STDDATA_VECTORITERATOR_H_ */