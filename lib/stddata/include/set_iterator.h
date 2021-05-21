#ifndef STDDATA_SET_ITERATOR_H_
#define STDDATA_SET_ITERATOR_H_

#include <assert.h>
#include "set.h"

typedef struct {
    Set set;
    int index;
} SetIterator;

#define SETFOR(set, iter) \
    for(SetIterator iter = SetBegin(set); \
        SetIteratorLess(iter, SetEnd(set)); \
        SetIteratorIncr(&iter))

/*
 * Returns an iterator to the beginning of the list
 */
SetIterator SetBegin(Set set);

/*
 * Returns an iterator to the end of the list
 */
SetIterator SetEnd(Set set);

/*
 * Checks if the first iterator points before the second
 */
bool SetIteratorLess(SetIterator a, SetIterator b);

/*
 * Comparator function for set iterators
 */
int SetIteratorCompare(SetIterator a, SetIterator b);

/*
 * Advances the iterator to the next item in the set
 * The iterator cannot be pointing to the end of the list
 */
void SetIteratorIncr(SetIterator *iter);

/* 
 * Retreats the iterator to the previous item in the set
 * The iterator cannot be pointing to the beginning of the list
 */
void SetIteratorDecr(SetIterator *iter);

/*
 * Returns the value of the item the iterator is pointing to
 */
void* SetIteratorGet(SetIterator iter);


#endif /* STDDATA_SET_ITERATOR_H_ */